/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests Sphere
*/

#include <criterion/criterion.h>
#include "Sphere.hpp"

using RayTracer::Sphere;
using RayTracer::Vector3D;
using RayTracer::Ray;
using RayTracer::Color;

Test(Sphere, touche_de_face)
{
    Sphere s(Vector3D(0, 0, 5), 1, Color{255, 0, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = s.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_float_eq(hit->distance, 4, 1e-6);
}

Test(Sphere, rayon_rate)
{
    Sphere s(Vector3D(0, 0, 5), 1, Color{255, 0, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 1, 0)};
    auto hit = s.hits(rayon);
    cr_assert_not(hit.has_value());
}

Test(Sphere, sphere_derriere)
{
    Sphere s(Vector3D(0, 0, -5), 1, Color{255, 0, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = s.hits(rayon);
    cr_assert_not(hit.has_value());
}

Test(Sphere, couleur_correcte)
{
    Sphere s(Vector3D(0, 0, 5), 1, Color{255, 128, 64});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = s.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_eq(hit->color.r, 255);
    cr_assert_eq(hit->color.g, 128);
    cr_assert_eq(hit->color.b, 64);
}

Test(Sphere, normale_correcte)
{
    Sphere s(Vector3D(0, 0, 5), 1, Color{255, 0, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = s.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_float_eq(hit->normal.z, -1, 1e-6);
}
