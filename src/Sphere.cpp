/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include "macros.hpp"
#include <cmath>

namespace RayTracer {

Sphere::Sphere(Vector3D center, double radius, Color color,
    double reflection, double transparency, double refraction)
    : _center(center), _radius(radius), _color(color),
    _reflection(reflection), _transparency(transparency),
    _refraction(refraction)
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
    return HitRecord{point, normal, t, _color,
        _reflection, _transparency, _refraction};
}

} // namespace RayTracer
