 /*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include "Factory.hpp"
#include <limits>

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

double DirectionalLight::getDistance(
    const Vector3D &point) const
{
    (void)point;
    return std::numeric_limits<double>::infinity();
}

} // namespace RayTracer

#ifdef PLUGIN_BUILD
extern "C" {
    void registerLight(
        RayTracer::Factory<RayTracer::ILight> &factory)
    {
        factory.registerType("directional",
            [](const libconfig::Setting &cfg) {
            return std::make_unique<RayTracer::DirectionalLight>(
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]), 1.0);
        });
    }
}
#endif
