/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Scene
*/

#include "Scene.hpp"

namespace RayTracer {

void Scene::addPrimitive(std::unique_ptr<IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void Scene::addLight(std::unique_ptr<ILight> light)
{
    _lights.push_back(std::move(light));
}

std::optional<HitRecord> Scene::getClosestHit(const Ray &ray) const
{
    std::optional<HitRecord> closest;

    for (const auto &primitive : _primitives) {
        auto hit = primitive->hits(ray);
        if (!hit)
            continue;
        if (!closest || hit->distance < closest->distance)
            closest = hit;
    }
    return closest;
}

const std::vector<std::unique_ptr<ILight>> &Scene::getLights() const
{
    return _lights;
}

void Scene::setAmbient(double ambient)
{
    _ambient = ambient;
}

double Scene::getAmbient() const
{
    return _ambient;
}

void Scene::setDiffuse(double diffuse)
{
    _diffuse = diffuse;
}

double Scene::getDiffuse() const
{
    return _diffuse;
}

} // namespace RayTracer
