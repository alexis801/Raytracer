/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneNode
*/

#include "SceneNode.hpp"

namespace RayTracer {

SceneNode::SceneNode()
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::addChild(std::unique_ptr<IPrimitive> child)
{
    _children.push_back(child);
}

std::optional<HitRecord> SceneNode::hits(const Ray &ray) const
{
    std::optional<HitRecord> closest;

    for (const auto &child : _children) {
        auto hit = child->hits(ray);
        if (hit && (!closest || hit->distance < closest->distance))
            closest = hit;
    }
    return closest;
}

}
