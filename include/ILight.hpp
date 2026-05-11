/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ILight
*/

#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "types.hpp"

namespace RayTracer {

/**
 * @class ILight
 * @brief Interface des lumieres
 */
class ILight {
public:
    virtual ~ILight() = default;

    /**
     * @brief Direction de la lumiere depuis un point
     * @param point le point eclaire
     */
    virtual Vector3D getDirection(const Vector3D &point) const = 0;

    /**
     * @brief Intensite de la lumiere en un point
     * @param point le point eclaire
     */
    virtual double getIntensity(const Vector3D &point) const = 0;

    /**
     * @brief Distance entre un point et la source de lumiere
     * @param point le point eclaire
     */
    virtual double getDistance(const Vector3D &point) const = 0;

    /**
     * @brief Couleur de la lumiere
     */
    virtual Color getColor() const = 0;
};

} // namespace RayTracer

#endif // ILIGHT_HPP_
