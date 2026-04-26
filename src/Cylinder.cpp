/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

#include <cmath>


namespace RayTracer {

Cylinder::Cylinder(Vector3D center, double radius, Color color)
    : _center(center), _radius(radius), _color(color)
{

}

std::optional<double> Cylinder::quadratic(const Ray &ray) const
{
    Vector3D oc = ray.origin - _center;
    double A = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double B = 2 * (oc.x * ray.direction.x + oc.z * ray.direction.z);
    double C = oc.x * oc.x + oc.z * oc.z - (_radius * _radius);

    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
        return std::nullopt;

    double t1 = (-B - std::sqrt(discriminant)) / (2 * A);
    double t2 = (-B + std::sqrt(discriminant)) / (2 * A);

    double t = t1;
    if (t < 0)
        t = t2;
    if (t < 0)
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
    rec.color = _color;
    return rec;
}

}