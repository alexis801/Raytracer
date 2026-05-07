/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "Factory.hpp"

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

#ifdef PLUGIN_BUILD
extern "C" {
    void registerLight(
        RayTracer::Factory<RayTracer::ILight> &factory)
    {
        factory.registerType("point",
            [](const libconfig::Setting &cfg) {
            return std::make_unique<RayTracer::PointLight>(
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]), 1.0);
        });
    }
}
#endif
