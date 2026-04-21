/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {

/**
 * @class PointLight
 * @brief Lumiere ponctuelle
 */
class PointLight : public ILight {
public:
    PointLight(Vector3D position, double intensity);
    ~PointLight() override = default;

    PointLight(const PointLight &other) = default;
    PointLight &operator=(const PointLight &other) = default;
    PointLight(PointLight &&other) = default;
    PointLight &operator=(PointLight &&other) = default;

    /**
     * @brief Direction vers la lumiere depuis un point
     * @param point point eclaire
     */
    Vector3D getDirection(const Vector3D &point) const override;

    /**
     * @brief Intensite de la lumiere en un point
     * @param point point eclaire
     */
    double getIntensity(const Vector3D &point) const override;

private:
    Vector3D _position;
    double _intensity;
};

} // namespace RayTracer

#endif // POINTLIGHT_HPP_
