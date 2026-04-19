/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
#define IPRIMITIVE_HPP_

#include "types.hpp"
#include <optional>

namespace RayTracer {

/**
 * @class IPrimitive
 * @brief Interface des formes 3D
 */
class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    /**
     * @brief Teste si un rayon touche la forme
     * @param ray Rayon a tester
     */
    virtual std::optional<HitRecord> hits(const Ray &ray) const = 0;
};

} // namespace RayTracer

#endif // IPRIMITIVE_HPP_
