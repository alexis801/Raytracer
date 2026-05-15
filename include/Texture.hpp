/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "types.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>
#include <vector>

namespace RayTracer {

class Texture {
public:
    Texture() = default;
    ~Texture() = default;
    bool load(const std::string &path);
    Color sample(double u, double v) const;
    bool isLoaded() const;

private:
    std::vector<unsigned char> _pixels;
    int _width = 0;
    int _height = 0;
    bool _loaded = false;
};

inline std::shared_ptr<Texture> parseTexture(
    const libconfig::Setting &cfg)
{
    if (!cfg.exists("texture"))
        return nullptr;
    std::string path = cfg["texture"];
    auto tex = std::make_shared<Texture>();
    if (!tex->load(path))
        return nullptr;
    return tex;
}

inline Color parseColor(const libconfig::Setting &cfg)
{
    if (!cfg.exists("color"))
        return {255, 255, 255};
    const auto &col = cfg["color"];
    return {col["r"], col["g"], col["b"]};
}

} // namespace RayTracer

#endif
