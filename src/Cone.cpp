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

    //coefficient a de l'equation addapter selon l'axe princ du cone
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

    //coefficient b de l'equation = croisement entre origine & direction
    double b = 0.0;

    if (_axis == "Y") {
        b = 2.0 * (oc.x * ray.direction.x + oc.z *
            ray.direction.z - k2 * oc.y * ray.direction.y);
    } else if (_axis == "X") {
        b = 2.0 * (oc.y * ray.direction.y + oc.z *
            ray.direction.z - k2 * oc.x * ray.direction.x);
    } else if (_axis == "Z") {
        b = 2.0 * (oc.x * ray.direction.x + oc.y *
            ray.direction.y - k2 * oc.z * ray.direction.z);
    }

    //coefficient c de l'equation = depend de l'oirigine du rayon (apex)
    double c = 0.0;

    if (_axis == "Y") {
        c = oc.x * oc.x + oc.z * oc.z - k2 * oc.y * oc.y;
    } else if (_axis == "X") {
        c = oc.y * oc.y + oc.z * oc.z - k2 * oc.x * oc.x;
    } else if (_axis == "Z") {
        c = oc.x * oc.x + oc.y * oc.y - k2 * oc.z * oc.z;
    }
    // discriminant de l'equation du second degre
    double discriminant = b * b - 4.0 * a * c;

    // pas d'intersection
    if (discriminant < 0) {
        return std::nullopt;
    }

    //affichage_debug pixel qui touche le cone;
    static int hits_count = 0;
    if (hits_count < 3) {
        std::cerr << "[DEBUG] Cone::hits HIT detected!"
                  << " a=" << a << " b=" << b << " c=" << c
                  << " discriminant=" << discriminant << "\n";
        hits_count++;
    }
    return std::nullopt;
}

} // namespace RayTracer