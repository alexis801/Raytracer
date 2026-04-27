/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.cpp
*/

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

    // resoluition equation quadratic 2 solutions
    // t1 t2 = 2 points ou le rayon traverse.
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-b - sqrtDisc) / (2.0 * a);
    double t2 = (-b + sqrtDisc) / (2.0 * a);
    double t = t1;

    // si t1 negatif on prend t2
    if (t < EPSILON) {
        t = t2;
        if (t < EPSILON) {
            return std::nullopt;
        }
    }
    // point impact = origine + direction * t
    Vector3D hitPoint = ray.origin + ray.direction * t;


    // Normale surface Cone, Normale = gradient de l'equation. axe principale et les 2 autres axes = coordonnee locale.
    Vector3D local = hitPoint - _apex;
    Vector3D normal(0.0, 1.0, 0.0);

    if (_axis == "Y") {
        normal = Vector3D(local.x, -k2 * local.y, local.z).normalize();
    } else if (_axis == "X") {
        normal = Vector3D(-k2 * local.x, local.y, local.z).normalize();
    } else if (_axis == "Z") {
        normal = Vector3D(local.x, local.y, -k2 * local.z).normalize();
    }
    return HitRecord{hitPoint, normal, t, _color, 0.0};
}

} // namespace RayTracer