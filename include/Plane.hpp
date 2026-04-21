/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "IPrimitive.hpp"
#include <string>

namespace RayTracer {

/**
 * @class Plane
 * @brief Surface plate
 */
class Plane : public IPrimitive {
public:
    Plane(const std::string &axis, double position, Color color);
    ~Plane() override = default;

    Plane(const Plane &other) = default;
    Plane &operator=(const Plane &other) = default;
    Plane(Plane &&other) = default;
    Plane &operator=(Plane &&other) = default;

    /**
     * @brief Teste si un rayon touche le plan
     * @param ray rayon a tester
     */
    std::optional<HitRecord> hits(const Ray &ray) const override;

private:
    std::string _axis;
    double _position;
    Color _color;
};

} // namespace RayTracer

#endif // PLANE_HPP_
