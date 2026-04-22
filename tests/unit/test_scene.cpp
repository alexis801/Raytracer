/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests Scene
*/

#include <criterion/criterion.h>
#include "Scene.hpp"
#include "Sphere.hpp"

using RayTracer::Scene;
using RayTracer::Sphere;
using RayTracer::Vector3D;
using RayTracer::Ray;
using RayTracer::Color;

Test(Scene, scene_vide_aucun_hit)
{
    Scene scene;
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = scene.getClosestHit(rayon);
    cr_assert_not(hit.has_value());
}

Test(Scene, objet_le_plus_proche)
{
    Scene scene;
    scene.addPrimitive(std::make_unique<Sphere>(
        Vector3D(0, 0, 10), 1, Color{255, 0, 0}));
    scene.addPrimitive(std::make_unique<Sphere>(
        Vector3D(0, 0, 5), 1, Color{0, 255, 0}));
    Ray rayon{Vector3D(0, 0, 0), Vector3D(0, 0, 1)};
    auto hit = scene.getClosestHit(rayon);
    cr_assert(hit.has_value());
    cr_assert_eq(hit->color.g, 255);
}

Test(Scene, ambiant_par_defaut)
{
    Scene scene;
    cr_assert_float_eq(scene.getAmbient(), 0.0, 1e-6);
}

Test(Scene, changer_ambiant)
{
    Scene scene;
    scene.setAmbient(0.4);
    cr_assert_float_eq(scene.getAmbient(), 0.4, 1e-6);
}
