/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"


namespace RayTracer {

Cylinder::Cylinder(Vector3D center, double radius, Color color)
    : _center(center), _radius(radius), _color(color)
{

}

std::optional<HitRecord> Cylinder::hits(const Ray &ray) const
{
    Vector3D oc = ray.origin - _center;
    double dx = ray.direction.x;
    double dz = ray.direction.z;
    double ox = oc.x;
    double oz = oc.z;

    double A = dx * dx + dz * dz;
    double B = 2 * (ox * dx + oz * dz);
    double C = ox * ox + oz * oz - (_radius * _radius);
}

}