/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.cpp
*/

#include <cmath>

#include "Cone.hpp"
#include "Factory.hpp"
#include "macros.hpp"

namespace RayTracer {

Cone::Cone(const std::string &axis, Vector3D apex, double angle,
    Color color, double reflection, double transparency,
    double refraction)
    : _axis(axis), _apex(apex), _angle(angle), _color(color),
    _reflection(reflection), _transparency(transparency),
    _refraction(refraction)
{

}

void Cone::ComputeQuadraticCoefficients(const Ray &ray, double k2, double &a, double &b, double &c) const
{
    // translate rayon = Cone a l'origine
    // Centre du cone a 0 pour les claculs
    Vector3D oc = ray.origin - _apex;

    //coefficient a de l'equation depend de la direction du cone
    //coefficient b de l'equation = croisement entre origine & direction
    //coefficient c de l'equation = depend de l'oirigine du rayon (apex)
    if (_axis == "Y") {
        a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - k2 *  ray.direction.y * ray.direction.y;
        b = 2.0 * (oc.x * ray.direction.x + oc.z * ray.direction.z - k2 * oc.y * ray.direction.y);
        c = oc.x * oc.x + oc.z * oc.z - k2 * oc.y * oc.y;
    } else if (_axis == "X") {
        a = ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z - k2 * ray.direction.x * ray.direction.x;
        b = 2.0 * (oc.y * ray.direction.y + oc.z * ray.direction.z - k2 * oc.x * ray.direction.x);
        c = oc.y * oc.y + oc.z * oc.z - k2 * oc.x * oc.x;
    } else if (_axis == "Z") {
        a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y - k2 * ray.direction.z * ray.direction.z;
        b = 2.0 * (oc.x * ray.direction.x + oc.y * ray.direction.y - k2 * oc.z * ray.direction.z);
        c = oc.x * oc.x + oc.y * oc.y - k2 * oc.z * oc.z;
    }
}

Vector3D Cone::ComputeNormal(const Vector3D &hitPoint, double k2) const
{
    // Normale = gradient de l'equation axe principale et les 2 autres axes = coordonnee locale.
    // axe principale recoit -k^2 pointe vers l'exterieur
    // 2 autre axe = coordone locale brut
    Vector3D local = hitPoint - _apex;

    if (_axis == "Y")
        return Vector3D(local.x, -k2 * local.y, local.z).normalize();
    if (_axis == "X")
        return Vector3D(-k2 * local.x, local.y, local.z).normalize();
    return Vector3D(local.x, local.y, -k2 * local.z).normalize();
}

std::optional<HitRecord> Cone::hits(const Ray &ray) const
{
    // k = tan (half angle ouverture)
    // equation = x^2 + z^2 = k^2 * y^2 (axe y)
    double k = std::tan(DEG_TO_RAD(_angle));
    double k2 = k * k;

    //calcul 3 coef de l'equation a*t^2 + b*t + c = 0
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    ComputeQuadraticCoefficients(ray, k2, a, b, c);


    // discriminant de l'equation : si negatif le rayon touche pas
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0) {
        return std::nullopt;
    }

    // resoluition equation quadratic 2 racines = 2 point intersections
    // garder le plus petit de t > EPSILON
    double sqrtDisc = std::sqrt(discriminant);
    double t1 = (-b - sqrtDisc) / (2.0 * a);
    double t2 = (-b + sqrtDisc) / (2.0 * a);
    double t = t1;

    if (t < EPSILON) {
        t = t2;
        if (t < EPSILON) {
            return std::nullopt;
        }
    }

    // Construction hitrecord avec point / normale / couleur
    Vector3D hitPoint = ray.origin + ray.direction * t;
    Vector3D normal = ComputeNormal(hitPoint, k2);
    return HitRecord{hitPoint, normal, t, _color, _reflection, _transparency, _refraction};
}

} // namespace RayTracer

static void parseMaterial(const libconfig::Setting &cfg,
    double &refl, double &transp, double &refr)
{
    refl = cfg.exists("reflection") ? (double)cfg["reflection"] : 0.0;
    transp = cfg.exists("transparency") ? (double)cfg["transparency"] : 0.0;
    refr = cfg.exists("refraction") ? (double)cfg["refraction"] : 1.0;
}

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("cone",
            [](const libconfig::Setting &cfg) {
            const auto &col = cfg["color"];
            double r;
            double t;
            double i;
            parseMaterial(cfg, r, t, i);
            return std::make_unique<RayTracer::Cone>(
                cfg["axis"],
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]),
                (double)cfg["angle"],
                RayTracer::Color{col["r"], col["g"],
                    col["b"]},
                r, t, i);
        });
    }
}
#endif
