/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

namespace RayTracer {

Cone::Cone(const std::string &axis, Vector3D apex, double angle,
    Color color) : _axis(axis), _apex(apex), _angle(angle), _color(color)
{

}

std::optional<HitRecord> Cone::hits(const Ray &ray) const
{

    // Pour l'instant le cone touche jamais rayon
    // ajout calcul intersection ici
    (void)ray;
    return std::nullopt;
}

} // namespace RayTracer