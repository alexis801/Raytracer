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

}

}