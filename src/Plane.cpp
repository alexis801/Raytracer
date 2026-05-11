/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

#include "Plane.hpp"
#include "Factory.hpp"
#include "macros.hpp"

namespace RayTracer {

Plane::Plane(const std::string &axis, double position,
    Color color, double reflection, double transparency,
    double refraction, double specular, double shininess)
    : _axis(axis), _position(position), _color(color),
    _reflection(reflection), _transparency(transparency),
    _refraction(refraction), _specular(specular),
    _shininess(shininess)
{
}

std::optional<HitRecord> Plane::hits(const Ray &ray) const
{
    Vector3D normal;
    double rayOriginOnAxis = 0;
    double rayDirOnAxis = 0;

    if (_axis == "X") {
        normal = Vector3D(1, 0, 0);
        rayOriginOnAxis = ray.origin.x;
        rayDirOnAxis = ray.direction.x;
    } else if (_axis == "Y") {
        normal = Vector3D(0, 1, 0);
        rayOriginOnAxis = ray.origin.y;
        rayDirOnAxis = ray.direction.y;
    } else {
        normal = Vector3D(0, 0, 1);
        rayOriginOnAxis = ray.origin.z;
        rayDirOnAxis = ray.direction.z;
    }
    if (std::abs(rayDirOnAxis) < EPSILON)
        return std::nullopt;
    double t = (_position - rayOriginOnAxis) / rayDirOnAxis;
    if (t < EPSILON)
        return std::nullopt;
    Vector3D point = ray.origin + ray.direction * t;
    return HitRecord{point, normal, t, _color,
        _reflection, _transparency, _refraction, _specular, _shininess};
}

} // namespace RayTracer

static void parseMaterial(const libconfig::Setting &cfg,
    double &refl, double &transp, double &refr, double &spec, double &shin)
{
    refl = cfg.exists("reflection")
        ? (double)cfg["reflection"] : 0.0;
    transp = cfg.exists("transparency")
        ? (double)cfg["transparency"] : 0.0;
    refr = cfg.exists("refraction")
        ? (double)cfg["refraction"] : 1.0;
    spec = cfg.exists("specular")
        ? (double)cfg["specular"] : 0.0;
    shin = cfg.exists("shininess")
        ? (double)cfg["shininess"] : 0.0;
}

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("plane",
            [](const libconfig::Setting &cfg) {
            const auto &col = cfg["color"];
            double r, t, i, spec, shin;
            parseMaterial(cfg, r, t, i, spec, shin);
            return std::make_unique<RayTracer::Plane>(
                cfg["axis"],
                (double)cfg["position"],
                RayTracer::Color{col["r"], col["g"],
                    col["b"]}, r, t, i, spec, shin);
        });
    }
}
#endif
