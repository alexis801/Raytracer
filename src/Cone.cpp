/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.cpp
*/

#include <iostream>

#include "Cone.hpp"

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

    
    // test affichage 1er pixel : debug
    static bool first = true;
    if (first) {
        std::cerr << "Cone::hits oc=("
            << oc.x << "," << oc.y << "," << oc.z << ") ray.dir=(" << ray.direction.x << "," << ray.direction.y << "," << ray.direction.z << ")\n";
        first = false;
    }
    // ajout calcul intersection ici
    return std::nullopt;
}

} // namespace RayTracer