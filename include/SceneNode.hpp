/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SceneNodeNode
*/

#ifndef SceneNodeNODE_HPP_
#define SceneNodeNODE_HPP_

#include "IPrimitive.hpp"
#include "ILight.hpp"
#include <memory>
#include <map>
#include <vector>

namespace RayTracer {

class SceneNode : public IPrimitive {
public:
    SceneNode() = default;
    ~SceneNode() = default;

    SceneNode(const SceneNode &other) = delete;
    SceneNode &operator=(const SceneNode &other) = delete;
    SceneNode(SceneNode &&other) = default;
    SceneNode &operator=(SceneNode &&other) = default;

    void addChild(std::unique_ptr<IPrimitive> child);

    std::optional<HitRecord> hits(const Ray &ray) const override;

private:
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
};

}

#endif /* !SceneNodeNODE_HPP_ */
