/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"

#include <libconfig.h++>
#include <stdexcept>

namespace RayTracer {

SceneParser::SceneParser()
{
    loadPlugins();
}

void SceneParser::loadPlugins()
{
    _pluginManager.loadAll(_primitiveFactory, _lightFactory);
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

void SceneParser::parsePrimitives(const libconfig::Setting &prims,
    Scene &scene) const
{
    if (!prims.exists("objects"))
        return;
    const auto &list = prims["objects"];

    for (int i = 0; i < list.getLength(); i++) {
        scene.addPrimitive(
            createNode(list[i])
        );
    }
}

std::unique_ptr<IPrimitive> SceneParser::createNode(
    const libconfig::Setting &cfg) const
{
    std::string type = cfg["type"];

    if (type == "group") {
        auto group = std::make_unique<GroupNode>();
        if (cfg.exists("objects")) {
            const auto &component = cfg["objects"];
            for (int i = 0; i < component.getLength(); i++) {
                group->addComponent(createNode(component[i]));
            }
        }
        return group;
    }
    auto primitive = _primitiveFactory.create(type, cfg);
    if (!primitive)
        throw std::runtime_error("primitive problem: " + type);
    return std::make_unique<PrimitiveNode>(std::move(primitive));
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
        for (int i = 0; i < dirs.getLength(); i++)
            scene.addLight(
                _lightFactory.create("directional", dirs[i]));
    }
    if (lights.exists("point")) {
        const auto &pts = lights["point"];
        for (int i = 0; i < pts.getLength(); i++)
            scene.addLight(
                _lightFactory.create("point", pts[i]));
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
