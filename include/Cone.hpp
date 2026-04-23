/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include <string>

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

    Cone(const std::string &axis, const Vector3D apex, double angle, const Color color);
    ~Cone() override = default;

    std ::optional<HitRecord> hits(const Ray &ray) const override;

    private:
        std::string _axis; // axe symetrique du cone (x, y ou z)
        Vector3D _apex; // sommet du cone : pointe
        double _angle; // angle ouverture du cone en degrés
        Color _color; // couleur cone
};

} // namespace RayTracer

#endif // CONE_HPP_