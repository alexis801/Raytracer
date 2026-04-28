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

class PrimitiveNode : public IPrimitive {
    public:
        PrimitiveNode(std::unique_ptr<IPrimitive> primitive)
            : _primitive(std::move(primitive)) {}

        std::optional<HitRecord> hits(const Ray &ray) const override {
            return _primitive->hits(ray);
        }

    private:
        std::unique_ptr<IPrimitive> _primitive;
};

class GroupNode : public IPrimitive {
    public:
        void addChild(std::unique_ptr<IPrimitive> child);

        std::optional<HitRecord> hits(const Ray &ray) const override;

    private:
        std::vector<std::unique_ptr<IPrimitive>> _children;
};

}

#endif /* !SceneNodeNODE_HPP_ */
