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
    Color color, double height)
    : _axis(axis), _apex(apex), _angle(angle), _color(color),
      _height(height)
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

bool Cone::isInsideHeight(const Vector3D &point) const
{
    if (_height <= 0)
        return true;
    Vector3D local = point - _apex;
    double axial = local.y;

    if (_axis == "X")
        axial = local.x;
    else if (_axis == "Z")
        axial = local.z;
    return std::fabs(axial) <= _height;
}

double Cone::findClosestRoot(const Ray &ray, double t1,
    double t2) const
{
    double t = -1.0;

    for (double candidate : {t1, t2}) {
        if (candidate < EPSILON)
            continue;
        if (!isInsideHeight(ray.origin + ray.direction * candidate))
            continue;
        if (t < 0 || candidate < t)
            t = candidate;
    }
    return t;
}

std::optional<HitRecord> Cone::hits(const Ray &ray) const
{
    double tan = std::tan(DEG_TO_RAD(_angle));
    double k2 = tan * tan;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    ComputeQuadraticCoefficients(ray, k2, a, b, c);
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0)
        return std::nullopt;
    double sqrtDisc = std::sqrt(discriminant);
    double t = findClosestRoot(ray, (-b - sqrtDisc) / (2.0 * a),
        (-b + sqrtDisc) / (2.0 * a));
    if (t < 0)
        return std::nullopt;
    Vector3D hitPoint = ray.origin + ray.direction * t;
    return HitRecord{hitPoint, ComputeNormal(hitPoint, k2), t,
        _color, 0.0};
}

} // namespace RayTracer

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("cone",
            [](const libconfig::Setting &cfg) {
            const auto &col = cfg["color"];
            double height = 0.0;
            if (cfg.exists("height"))
                height = (double)cfg["height"];
            return std::make_unique<RayTracer::Cone>(
                cfg["axis"],
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]),
                (double)cfg["angle"],
                RayTracer::Color{col["r"], col["g"],
                    col["b"]}, height);
        });
    }
}
#endif
