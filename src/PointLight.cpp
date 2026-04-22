/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"

namespace RayTracer {

PointLight::PointLight(Vector3D position, double intensity)
    : _position(position), _intensity(intensity)
{
}

Vector3D PointLight::getDirection(const Vector3D &point) const
{
    return (_position - point).normalize();
}

double PointLight::getIntensity(const Vector3D &point) const
{
    (void)point;
    return _intensity;
}

double PointLight::getDistance(const Vector3D &point) const
{
    return (_position - point).length();
}

} // namespace RayTracer
