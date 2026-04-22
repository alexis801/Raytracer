/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests Plane
*/

#include <criterion/criterion.h>
#include "Plane.hpp"

using RayTracer::Plane;
using RayTracer::Vector3D;
using RayTracer::Ray;
using RayTracer::Color;

Test(Plane, touche_axe_z)
{
    Plane p("Z", -5, Color{0, 0, 255});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, -1)};
    auto hit = p.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_float_eq(hit->distance, 5, 1e-6);
}

Test(Plane, rayon_parallele)
{
    Plane p("Z", -5, Color{0, 0, 255});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(1, 0, 0)};
    auto hit = p.hits(rayon);
    cr_assert_not(hit.has_value());
}

Test(Plane, plan_derriere)
{
    Plane p("Z", 5, Color{0, 0, 255});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, -1)};
    auto hit = p.hits(rayon);
    cr_assert_not(hit.has_value());
}

Test(Plane, touche_axe_y)
{
    Plane p("Y", 10, Color{0, 255, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 1, 0)};
    auto hit = p.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_float_eq(hit->distance, 10, 1e-6);
}

Test(Plane, touche_axe_x)
{
    Plane p("X", 3, Color{255, 0, 0});
    Ray rayon{Vector3D(0, 0, 0), Vector3D(1, 0, 0)};
    auto hit = p.hits(rayon);
    cr_assert(hit.has_value());
    cr_assert_float_eq(hit->distance, 3, 1e-6);
}
