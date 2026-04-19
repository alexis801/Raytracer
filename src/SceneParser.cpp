/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include "macros.hpp"
#include <libconfig.h++>
#include <stdexcept>

namespace RayTracer {

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
}

} // namespace RayTracer
