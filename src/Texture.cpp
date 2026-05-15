/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Texture
*/

#include "Texture.hpp"
#include <SFML/Graphics/Image.hpp>
#include <algorithm>
#include <cmath>

namespace RayTracer {

bool Texture::load(const std::string &path)
{
    sf::Image image;
    if (!image.loadFromFile(path)) {
        _loaded = false;
        return false;
    }
    auto size = image.getSize();
    _width = static_cast<int>(size.x);
    _height = static_cast<int>(size.y);
    const sf::Uint8 *src = image.getPixelsPtr();
    _pixels.assign(src, src + static_cast<size_t>(_width) * _height * 4);
    _loaded = true;
    return true;
}

Color Texture::sample(double u, double v) const
{
    if (!_loaded || _width <= 0 || _height <= 0)
        return {255, 255, 255};

    u = u - std::floor(u);
    v = v - std::floor(v);
    int x = std::clamp(static_cast<int>(u * _width), 0, _width - 1);
    int y = std::clamp(static_cast<int>(v * _height), 0, _height - 1);
    size_t idx = (static_cast<size_t>(y) * _width + x) * 4;
    return {
        static_cast<int>(_pixels[idx]),
        static_cast<int>(_pixels[idx + 1]),
        static_cast<int>(_pixels[idx + 2])
    };
}

bool Texture::isLoaded() const
{ 
    return _loaded;
}

} // namespace RayTracer
