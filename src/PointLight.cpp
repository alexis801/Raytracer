/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "Factory.hpp"

namespace RayTracer {

PointLight::PointLight(Vector3D position, double intensity,
    Color color)
    : _position(position), _intensity(intensity), _color(color)
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

Color PointLight::getColor() const
{
    return _color;
}

} // namespace RayTracer

#ifdef PLUGIN_BUILD
extern "C" {
    void registerLight(
        RayTracer::Factory<RayTracer::ILight> &factory)
    {
        factory.registerType("point",
            [](const libconfig::Setting &cfg) {
            RayTracer::Color color{255, 255, 255};
            if (cfg.exists("color")) {
                const auto &col = cfg["color"];
                color = RayTracer::Color{col["r"], col["g"],
                    col["b"]};
            }
            return std::make_unique<RayTracer::PointLight>(
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]), 1.0, color);
        });
    }
}
#endif
