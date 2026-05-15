/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "Factory.hpp"
#include "macros.hpp"
#include <cmath>
#include <libconfig.h++>

namespace RayTracer {

Sphere::Sphere(Vector3D center, double radius, Color color,
    double reflection, double transparency, double refraction,
    double specular, double shininess,
    std::shared_ptr<Texture> texture)
    : _center(center), _radius(radius), _color(color),
    _reflection(reflection), _transparency(transparency),
    _refraction(refraction), _specular(specular),
    _shininess(shininess), _texture(std::move(texture))
{
}

std::optional<HitRecord> Sphere::hits(const Ray &ray) const
{
    Vector3D originToCenter = ray.origin - _center;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * originToCenter.dot(ray.direction);
    double c = originToCenter.dot(originToCenter)
        - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return std::nullopt;
    double t = (-b - std::sqrt(discriminant)) / (2 * a);
    if (t < EPSILON) {
        t = (-b + std::sqrt(discriminant)) / (2 * a);
        if (t < EPSILON)
            return std::nullopt;
    }
    Vector3D point = ray.origin + ray.direction * t;
    Vector3D normal = (point - _center).normalize();
    Color color = _color;
    if (_texture && _texture->isLoaded()) {
        double u = 0.5 + std::atan2(normal.y, normal.x) / (2.0 * PI);
        double v = 0.5 - std::asin(std::clamp(normal.z, -1.0, 1.0)) / PI;
        color = _texture->sample(u, v);
    }
    return HitRecord{point, normal, t, color,
        _reflection, _transparency, _refraction, _specular, _shininess};
}

} // namespace RayTracer

static void parseMaterial(const libconfig::Setting &cfg,
    double &refl, double &transp, double &refr,
    double &spec, double &shin)
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
        factory.registerType("sphere",
            [](const libconfig::Setting &cfg) {
            double r, t, i, spec, shin;
            parseMaterial(cfg, r, t, i, spec, shin);
            return std::make_unique<RayTracer::Sphere>(
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]),
                (double)cfg["r"],
                RayTracer::parseColor(cfg), r, t, i, spec, shin,
                RayTracer::parseTexture(cfg));
        });
    }
}
#endif
