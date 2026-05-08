/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PluginManager
*/

#include "PluginManager.hpp"
#include "macros.hpp"
#include <filesystem>

namespace RayTracer {

void PluginManager::loadAll(
    Factory<IPrimitive> &primitiveFactory,
    Factory<ILight> &lightFactory)
{
    if (!std::filesystem::exists(PLUGINS_DIR))
        return;
    for (const auto &entry :
        std::filesystem::directory_iterator(PLUGINS_DIR)) {
        if (entry.path().extension() == PLUGIN_EXT)
            loadPlugin(entry.path().string(),
                primitiveFactory, lightFactory);
    }
}

void PluginManager::loadPlugin(const std::string &path,
    Factory<IPrimitive> &primitiveFactory,
    Factory<ILight> &lightFactory)
{
    _loaders.emplace_back(path);
    auto &loader = _loaders.back();
    try {
        auto reg = loader.getSymbol<
            void (*)(Factory<IPrimitive> &)>(
            "registerPrimitive");
        reg(primitiveFactory);
        return;
    } catch (...) {}
    try {
        auto reg = loader.getSymbol<
            void (*)(Factory<ILight> &)>(
            "registerLight");
        reg(lightFactory);
    } catch (...) {}
}

} // namespace RayTracer
