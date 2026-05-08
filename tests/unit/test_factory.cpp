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

static libconfig::Config &makeConfig()
{
    static libconfig::Config cfg;
    static bool init = false;
    if (!init) {
        cfg.readString(
            "obj = { type = \"sphere\"; x = 0.0; y = 0.0;"
            " z = 0.0; r = 1.0; color = { r = 255;"
            " g = 0; b = 0; }; };");
        init = true;
    }
    return cfg;
}

Test(Factory, save_et_creer)
{
    Factory<IPrimitive> factory;
    factory.registerType("sphere",
        [](const libconfig::Setting &cfg) {
        return std::make_unique<Sphere>(
            Vector3D(cfg["x"], cfg["y"], cfg["z"]),
            (double)cfg["r"],
            Color{cfg["color"]["r"], cfg["color"]["g"],
                cfg["color"]["b"]});
    });
    auto &config = makeConfig();
    auto obj = factory.create("sphere",
        config.lookup("obj"));
    cr_assert_not_null(obj.get());
}

Test(Factory, type_inconnu_egal_null)
{
    Factory<IPrimitive> factory;
    auto &config = makeConfig();
    auto obj = factory.create("inconnu",
        config.lookup("obj"));
    cr_assert_null(obj.get());
}

Test(Factory, type_egal_existe)
{
    Factory<IPrimitive> factory;
    factory.registerType("sphere",
        [](const libconfig::Setting &cfg) {
        (void)cfg;
        return std::make_unique<Sphere>(
            Vector3D(), 1.0, Color{});
    });
    cr_assert(factory.exists("sphere"));
    cr_assert_not(factory.exists("cone"));
}
