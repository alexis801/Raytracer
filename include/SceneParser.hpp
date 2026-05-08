/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** SceneParser
*/

#ifndef SCENEPARSER_HPP_
#define SCENEPARSER_HPP_

#include "Scene.hpp"
#include "Camera.hpp"
#include "Factory.hpp"
#include "PluginManager.hpp"
#include <string>

namespace libconfig {
    class Setting;
}

namespace RayTracer {

/**
 * @class SceneParser
 * @brief Lit un fichier .cfg et construit la scene
 */
class SceneParser {
public:
    SceneParser();
    ~SceneParser() = default;

    SceneParser(const SceneParser &other) = delete;
    SceneParser &operator=(const SceneParser &other) = delete;
    SceneParser(SceneParser &&other) = delete;
    SceneParser &operator=(SceneParser &&other) = delete;

    /**
     * @brief Parse le fichier et remplit la scene et la camera
     * @param filepath path .cfg
     * @param scene scene a remplir
     * @param camera camera a configurer
     */
    void parse(const std::string &filepath, Scene &scene,
        Camera &camera) const;
    
    std::unique_ptr<IPrimitive> createNode(const libconfig::Setting &cfg) const;

private:
    PluginManager _pluginManager;
    Factory<IPrimitive> _primitiveFactory;
    Factory<ILight> _lightFactory;

    void loadPlugins();
    Camera parseCamera(const libconfig::Setting &root) const;
    void parsePrimitives(const libconfig::Setting &prims,
        Scene &scene) const;
    void parseLights(const libconfig::Setting &root,
        Scene &scene) const;
};

} // namespace RayTracer

#endif // SCENEPARSER_HPP_
