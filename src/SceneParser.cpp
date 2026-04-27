/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Cone.hpp"

#include <libconfig.h++>
#include <stdexcept>
#include <iostream>

namespace RayTracer {

SceneParser::SceneParser()
{
    registerTypes();
}

void SceneParser::registerTypes()
{
    _primitiveFactory.registerType("sphere",
        []() { return std::make_unique<Sphere>(
            Vector3D(), 1.0, Color{}); });
    _primitiveFactory.registerType("plane",
        []() { return std::make_unique<Plane>(
            "Z", 0.0, Color{}); });
    _primitiveFactory.registerType("cone",
        []() { return std::make_unique<Cone>(
            "Y", Vector3D(), 30.0, Color{}); });
    _lightFactory.registerType("directional",
        []() { return std::make_unique<DirectionalLight>(
            Vector3D(0, -1, 0), 1.0); });
    _lightFactory.registerType("point",
        []() { return std::make_unique<PointLight>(
            Vector3D(), 1.0); });
    _lightFactory.registerType("cylinder",
        []() { return std::make_unique<Cylinder>(
            Vector3D(), 1.0); });
    std::cerr << "registerTypes: cone registered in primitive factory\n";
}

Camera SceneParser::parseCamera(
    const libconfig::Setting &root) const
{
    const auto &cam = root["camera"];
    const auto &res = cam["resolution"];
    const auto &pos = cam["position"];
    const auto &rot = cam["rotation"];
    int width = res["width"];
    int height = res["height"];
    double fov = cam["fieldOfView"];
    Vector3D position(pos["x"], pos["y"], pos["z"]);
    Vector3D rotation(rot["x"], rot["y"], rot["z"]);
    return Camera(width, height, position, rotation, fov);
}

void SceneParser::parsePrimitives(
    const libconfig::Setting &prims, Scene &scene) const
{
    if (prims.exists("spheres")) {
        const auto &list = prims["spheres"];
        for (int i = 0; i < list.getLength(); i++) {
            const auto &sphere = list[i];
            const auto &col = sphere["color"];
            Vector3D center(sphere["x"], sphere["y"],
                sphere["z"]);
            double radius = sphere["r"];
            Color color{col["r"], col["g"], col["b"]};
            double refl = 0.0;
            if (sphere.exists("reflection"))
                refl = sphere["reflection"];
            scene.addPrimitive(
                std::make_unique<Sphere>(
                    center, radius, color, refl));
        }
    }
    if (prims.exists("planes")) {
        const auto &list = prims["planes"];
        for (int i = 0; i < list.getLength(); i++) {
            const auto &plane = list[i];
            const auto &col = plane["color"];
            std::string axis = plane["axis"];
            double position = plane["position"];
            Color color{col["r"], col["g"], col["b"]};
            double refl = 0.0;
            if (plane.exists("reflection"))
                refl = plane["reflection"];
            scene.addPrimitive(
                std::make_unique<Plane>(
                    axis, position, color, refl));
        }
    }
    if (prims.exists("cones")) {
        const auto &list = prims["cones"];
        for (int i = 0; i < list.getLength(); i++) {
            const auto &cone = list[i];
            const auto &col = cone["color"];
            std::string axis = cone["axis"];
            Vector3D apex(cone["x"], cone["y"], cone["z"]);
            double angle = cone["angle"];
            Color color{col["r"], col["g"], col["b"]};
            scene.addPrimitive(
                std::make_unique<Cone>(axis, apex, angle, color));
            std::cerr << "parsed cone: axis =" << axis << " apex =(" << apex.x << "," << apex.y
                      << "," << apex.z << ") angle =" << angle << " colo r=(" << color.r << "," << color.g << "," << color.b << ")\n";
        }
    }
}

void SceneParser::parseLights(
    const libconfig::Setting &root, Scene &scene) const
{
    if (!root.exists("lights"))
        return;
    const auto &lights = root["lights"];
    if (lights.exists("ambient"))
        scene.setAmbient(lights["ambient"]);
    if (lights.exists("diffuse"))
        scene.setDiffuse(lights["diffuse"]);
    if (lights.exists("directional")) {
        const auto &dirs = lights["directional"];
        for (int i = 0; i < dirs.getLength(); i++) {
            Vector3D dir(dirs[i]["x"], dirs[i]["y"],
                dirs[i]["z"]);
            scene.addLight(
                std::make_unique<DirectionalLight>(dir, 1.0));
        }
    }
    if (lights.exists("point")) {
        const auto &pts = lights["point"];
        for (int i = 0; i < pts.getLength(); i++) {
            Vector3D pos(pts[i]["x"], pts[i]["y"],
                pts[i]["z"]);
            scene.addLight(
                std::make_unique<PointLight>(pos, 1.0));
        }
    }
}

void SceneParser::parse(const std::string &filepath,
    Scene &scene, Camera &camera) const
{
    libconfig::Config cfg;

    try {
        cfg.readFile(filepath.c_str());
    } catch (const libconfig::FileIOException &e) {
        throw std::runtime_error("Cannot read file: "
            + filepath);
    } catch (const libconfig::ParseException &e) {
        throw std::runtime_error("Parse error at line "
            + std::to_string(e.getLine()) + ": "
            + e.getError());
    }
    const auto &root = cfg.getRoot();
    camera = parseCamera(root);
    if (root.exists("primitives")) {
        const auto &prims = root["primitives"];
        parsePrimitives(prims, scene);
    }
    parseLights(root, scene);
}

} // namespace RayTracer
