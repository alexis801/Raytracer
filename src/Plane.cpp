/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

#include "Plane.hpp"
#include "macros.hpp"

namespace RayTracer {

Plane::Plane(const std::string &axis, double position,
    Color color, double reflection, double transparency,
    double refraction)
    : _axis(axis), _position(position), _color(color),
    _reflection(reflection), _transparency(transparency),
    _refraction(refraction)
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
        _reflection, _transparency, _refraction};
}

} // namespace RayTracer
