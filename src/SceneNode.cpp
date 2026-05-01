/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneNode
*/

#include "SceneNode.hpp"

namespace RayTracer {


void GroupNode::addComponent(std::unique_ptr<IPrimitive> child)
{
    _components.push_back(std::move(child));
}

std::optional<HitRecord> GroupNode::hits(const Ray &ray) const
{
    std::optional<HitRecord> closest;

    for (const auto &child : _components) {
        auto hit = child->hits(ray);
         if (!hit)
            continue;
        if (hit && (!closest || hit->distance < closest->distance))
            closest = hit;
    }
    return closest;
}

}
