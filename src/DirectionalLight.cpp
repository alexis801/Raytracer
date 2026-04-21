 /*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

namespace RayTracer {

DirectionalLight::DirectionalLight(Vector3D direction,
    double intensity)
    : _direction(direction.normalize()), _intensity(intensity)
{
}

Vector3D DirectionalLight::getDirection(
    const Vector3D &point) const
{
    (void)point;
    return _direction * -1;
}

double DirectionalLight::getIntensity(
    const Vector3D &point) const
{
    (void)point;
    return _intensity;
}

} // namespace RayTracer
