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
    double screenX = (2.0 * (x + 0.5) / _width - 1.0)
        * aspect * scale;
    double screenY = (1.0 - 2.0 * (y + 0.5) / _height) * scale;
    Vector3D direction(screenX, screenY, 1.0);
    direction = direction.rotateX(DEG_TO_RAD(_rotation.x));
    direction = direction.rotateY(DEG_TO_RAD(_rotation.y));
    direction = direction.rotateZ(DEG_TO_RAD(_rotation.z));
    return {_position, direction.normalize()};
}

int Camera::getWidth() const
{
    return _width;
}

int Camera::getHeight() const
{
    return _height;
}

void Camera::rotate(double verticalAngle, double horizontalAngle)
{
    _rotation.x += verticalAngle;
    _rotation.y += horizontalAngle;
}

void Camera::moveForward(double distance)
{
    Vector3D forward(0, 0, 1);
 
    forward = forward.rotateX(DEG_TO_RAD(_rotation.x));
    forward = forward.rotateY(DEG_TO_RAD(_rotation.y));
    _position = _position + forward * distance;
}

void Camera::moveRight(double distance)
{
    Vector3D right(1, 0, 0);

    right = right.rotateX(DEG_TO_RAD(_rotation.x));
    right = right.rotateY(DEG_TO_RAD(_rotation.y));
    _position = _position + right * distance;
}

} // namespace RayTracer
