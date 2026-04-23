/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include "IPrimitive.hpp"

namespace RayTracer {
/**
 * @class Cone
 * @brief Forme 3d en Pointe
 */

 class Cone : public IPrimitive {
    public:
    /**
     * @brief Test si le rayonn touche le cone
     * @param ray rayon a tester
     */

    std ::optional<HitRecord> hits(const Ray &ray) const override;
};

} // namespace RayTracer

#endif // CONE_HPP_