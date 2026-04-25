/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.cpp
*/

#include <iostream>
#include <cmath>

#include "Cone.hpp"
#include "macros.hpp"

namespace RayTracer {

Cone::Cone(const std::string &axis, Vector3D apex, double angle,
    Color color) : _axis(axis), _apex(apex), _angle(angle), _color(color)
{

}

std::optional<HitRecord> Cone::hits(const Ray &ray) const
{
    // translate rayon = Cone a l'origine
    // Centre du cone a 0 pour les claculs
    Vector3D oc = ray.origin - _apex;

    // k = tan (half angle ouverture)
    // equation = x^2 = z^2 = k^2 * y^2 (axe y)
    double k = std::tan(DEG_TO_RAD(_angle));
    double k2 = k * k;
    
    //coefficient de l'equation addapter selon l'axe princ du cone
    double a = 0.0;

    if (_axis == "Y") {
        a = ray.direction.x * ray.direction.x + ray.direction.z * 
            ray.direction.z - k2 *  ray.direction.y * ray.direction.y;
    } else if (_axis == "X") {
        a = ray.direction.y * ray.direction.y + ray.direction.z * 
            ray.direction.z - k2 * ray.direction.x * ray.direction.x;
    } else if (_axis == "Z") {
        a = ray.direction.x * ray.direction.x + ray.direction.y * 
            ray.direction.y - k2 * ray.direction.z * ray.direction.z;
    }

    double b = 0.0;

    if (_axis == "Y") {
        b = 2.0 * (oc.x * ray.direction.x + oc.z * ray.direction.z - k2 * oc.y * ray.direction.y);
    } else if (_axis == "X") {
    } else if (_axis == "Z") {
    }

    // test affichage 1er pixel : debug
    static bool first = true;
    if (first) {
        std::cerr << "cone::hits a=" << a << " b=" << b << "\n";
        first = false;
    }
    (void)oc;
    return std::nullopt;
}

} // namespace RayTracer