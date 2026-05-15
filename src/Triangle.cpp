/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#include <cmath>

#include "Triangle.hpp"
#include "Factory.hpp"
#include "macros.hpp"

namespace RayTracer {

Triangle::Triangle(Vector3D center, double radius, Color color,
    double height, double reflection, double transparency,
    double refraction, double specular, double shininess)
    : _center(center), _radius(radius), _color(color),
      _height(height), _reflection(reflection),
      _transparency(transparency), _refraction(refraction),
      _specular(specular), _shininess(shininess)
{
}


std::optional<HitRecord> Triangle::hits(const Ray &ray) const
{

}


}

static void parseMaterial(const libconfig::Setting &cfg,
    double &refl, double &transp, double &refr, double &spec, double &shin)
{
    refl = cfg.exists("reflection") ? (double)cfg["reflection"] : 0.0;
    transp = cfg.exists("transparency") ? (double)cfg["transparency"] : 0.0;
    refr = cfg.exists("refraction") ? (double)cfg["refraction"] : 1.0;
    spec = cfg.exists("specular") ? (double)cfg["specular"] : 0.0;
    shin = cfg.exists("shininess") ? (double)cfg["shininess"] : 0.0;
}

#ifdef PLUGIN_BUILD
extern "C" {
    void registerPrimitive(
        RayTracer::Factory<RayTracer::IPrimitive> &factory)
    {
        factory.registerType("triangle",
            [](const libconfig::Setting &cfg) {
            const auto &col = cfg["color"];
            double height = 0.0;
            if (cfg.exists("height"))
                height = (double)cfg["height"];
            double r, t, i, spec, shin;
            parseMaterial(cfg, r, t, i, spec, shin);
            return std::make_unique<RayTracer::Cone>(
                cfg["axis"],
                RayTracer::Vector3D(cfg["x"], cfg["y"],
                    cfg["z"]),
                (double)cfg["angle"],
                RayTracer::Color{col["r"], col["g"],
                    col["b"]},
                height, r, t, i, spec, shin);
        });
    }
}
#endif
