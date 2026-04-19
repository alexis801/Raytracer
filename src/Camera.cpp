/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"
#include "macros.hpp"
#include <cmath>

namespace RayTracer {

Camera::Camera(int width, int height, Vector3D position,
    Vector3D rotation, double fov)
    : _width(width), _height(height), _position(position),
      _rotation(rotation), _fov(fov)
{
}

Ray Camera::generateRay(int x, int y) const
{
    double aspect = static_cast<double>(_width) / _height;
    double scale = std::tan(DEG_TO_RAD(_fov / 2.0));
    double px = (2.0 * (x + 0.5) / _width - 1.0) * aspect * scale;
    double py = (1.0 - 2.0 * (y + 0.5) / _height) * scale;
    Vector3D direction = Vector3D(px, py, 1.0).normalize();
    return {_position, direction};
}

int Camera::getWidth() const
{
    return _width;
}

int Camera::getHeight() const
{
    return _height;
}

} // namespace RayTracer
