/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PluginManager
*/

#ifndef PLUGINMANAGER_HPP_
#define PLUGINMANAGER_HPP_

#include "DLLoader.hpp"
#include "Factory.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include <vector>
#include <string>

namespace RayTracer {

/**
 * @class PluginManager
 * @brief Charge les plugins depuis le dossier plugins/
 */
class PluginManager {
public:
    PluginManager() = default;
    ~PluginManager() = default;

    PluginManager(const PluginManager &other) = delete;
    PluginManager &operator=(const PluginManager &other) = delete;
    PluginManager(PluginManager &&other) = default;
    PluginManager &operator=(PluginManager &&other) = default;

    /**
     * @brief Charge tous les .so et enregistre dans les factories
     * @param primitiveFactory factory des formes
     * @param lightFactory factory des lumieres
     */
    void loadAll(Factory<IPrimitive> &primitiveFactory,
        Factory<ILight> &lightFactory);

private:
    std::vector<DLLoader> _loaders;

    void loadPlugin(const std::string &path,
        Factory<IPrimitive> &primitiveFactory,
        Factory<ILight> &lightFactory);
};

} // namespace RayTracer

#endif // PLUGINMANAGER_HPP_
