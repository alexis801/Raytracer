/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** tests Factory
*/

#include <criterion/criterion.h>
#include "Factory.hpp"
#include "IPrimitive.hpp"
#include "Sphere.hpp"

using RayTracer::Factory;
using RayTracer::IPrimitive;
using RayTracer::Sphere;
using RayTracer::Vector3D;
using RayTracer::Color;

Test(Factory, save_et_creer)
{
    Factory<IPrimitive> factory;
    factory.registerType("sphere", []() {
        return std::make_unique<Sphere>(
            Vector3D(), 1.0, Color{});
    });
    auto obj = factory.create("sphere");
    cr_assert_not_null(obj.get());
}

Test(Factory, type_inconnu_egal_null)
{
    Factory<IPrimitive> factory;
    auto obj = factory.create("inconnu");
    cr_assert_null(obj.get());
}

Test(Factory, type_egal_existe)
{
    Factory<IPrimitive> factory;
    factory.registerType("sphere", []() {
        return std::make_unique<Sphere>(
            Vector3D(), 1.0, Color{});
    });
    cr_assert(factory.exists("sphere"));
    cr_assert_not(factory.exists("cone"));
}
