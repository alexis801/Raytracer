/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Factory.hpp"

#include <cmath>


namespace RayTracer {

Cylinder::Cylinder(Vector3D center, double radius, Color color,
    double height)
    : _center(center), _radius(radius), _color(color),
      _height(height)
{

}

bool Cylinder::isValid(const Ray &ray, double t) const
{
    if (t < 0)
        return false;
    if (_height <= 0)
        return true;
    double y = ray.origin.y + ray.direction.y * t;
    return y >= _center.y && y <= _center.y + _height;
}

std::optional<double> Cylinder::quadratic(const Ray &ray) const
{
    Vector3D oc = ray.origin - _center;
    double A = ray.direction.x * ray.direction.x
        + ray.direction.z * ray.direction.z;
    double B = 2 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
    double C = oc.x * oc.x + oc.z * oc.z - (_radius * _radius);
    double discriminant = B * B - 4 * A * C;
    if (discriminant < 0)
        return std::nullopt;
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-B - sqrtDisc) / (2 * A);
    double t2 = (-B + sqrtDisc) / (2 * A);
    double t = isValid(ray, t1) ? t1 : t2;

    if (!isValid(ray, t))
        return std::nullopt;
    return t;
}

std::optional<HitRecord> Cylinder::hits(const Ray &ray) const
{

    std::optional<double> tOptional = quadratic(ray);
    if (tOptional == std::nullopt)
        return std::nullopt;

    double t = *tOptional;

    Vector3D hitPoint = ray.origin + ray.direction * t;

    Vector3D normal = Vector3D(hitPoint.x - _center.x, 0,
    hitPoint.z - _center.z).normalize();

    HitRecord rec;
    rec.point = hitPoint;
    rec.normal = normal;
    rec.distance = t;
    rec.color = _color;
    return rec;
}

} // namespace RayTracer

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("cylinder",
            [](const libconfig::Setting &cfg) {
            const auto &col = cfg["color"];
            double height = 0.0;
            if (cfg.exists("height"))
                height = (double)cfg["height"];
            return std::make_unique<RayTracer::Cylinder>(
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]),
                (double)cfg["r"],
                RayTracer::Color{col["r"], col["g"],
                    col["b"]}, height);
        });
    }
}
#endif
