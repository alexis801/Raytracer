/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle.cpp
*/

#include <cmath>
#include <optional>

#include "Triangle.hpp"
#include "Factory.hpp"
#include "macros.hpp"

namespace RayTracer {

Triangle::Triangle(
    Vector3D v0, Vector3D v1, Vector3D v2,
    Color color,
    double reflection,
    double transparency,
    double refraction,
    double specular,
    double shininess
) : _v0(v0), _v1(v1), _v2(v2),
    _normal(computeNormal()),
    _color(color),
    _reflection(reflection),
    _transparency(transparency),
    _refraction(refraction),
    _specular(specular),
    _shininess(shininess)
{
}

Vector3D Triangle::computeNormal() const
{
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;
    return edge1.cross(edge2).normalize();
}

bool Triangle::computeIntersection(const Ray &ray, double &u, double &v, double &t) const
{
    const double EPSILON = 1e-6;
    Vector3D edge1 = _v1 - _v0;
    Vector3D edge2 = _v2 - _v0;
    Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (std::fabs(a) < EPSILON)
        return false;

    double f = 1.0 / a;
    Vector3D s = ray.origin - _v0;
    u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return false;

    Vector3D q = s.cross(edge1);
    v = f * ray.direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    t = f * edge2.dot(q);
    return t > EPSILON;
}

std::optional<HitRecord> Triangle::hits(const Ray &ray) const
{
    double u, v, t;
    if (!computeIntersection(ray, u, v, t))
        return std::nullopt;

    Vector3D hitPoint = ray.origin + ray.direction * t;
    return HitRecord{
        hitPoint,
        _normal,
        t,
        _color,
        _reflection,
        _transparency,
        _refraction,
        _specular,
        _shininess
    };
}

} // namespace RayTracer

static void parseMaterial(const libconfig::Setting &cfg,
    double &refl, double &transp, double &refr, double &spec, double &shin)
{
    refl = cfg.exists("reflection") ? (double)cfg["reflection"] : 0.0;
    transp = cfg.exists("transparency") ? (double)cfg["transparency"] : 0.0;
    refr = cfg.exists("refraction") ? (double)cfg["refraction"] : 1.0;
    spec = cfg.exists("specular") ? (double)cfg["specular"] : 0.0;
    shin = cfg.exists("shininess") ? (double)cfg["shininess"] : 0.0;
}

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("triangle",
            [](const libconfig::Setting &cfg) {
                const auto &col = cfg["color"];
                double r, t, i, spec, shin;
                parseMaterial(cfg, r, t, i, spec, shin);
                return std::make_unique<RayTracer::Triangle>(
                    RayTracer::Vector3D(cfg["v0x"], cfg["v0y"], cfg["v0z"]),
                    RayTracer::Vector3D(cfg["v1x"], cfg["v1y"], cfg["v1z"]),
                    RayTracer::Vector3D(cfg["v2x"], cfg["v2y"], cfg["v2z"]),
                    RayTracer::Color{col["r"], col["g"], col["b"]},
                    r, t, i, spec, shin
                );
            });
    }
}
#endif
