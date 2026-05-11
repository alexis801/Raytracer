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
    PointLight(Vector3D position, double intensity,
        Color color = {255, 255, 255});
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

    /**
     * @brief Distance entre un point et la lumiere
     * @param point point eclaire
     */
    double getDistance(const Vector3D &point) const override;

    /**
     * @brief Couleur de la lumiere
     */
    Color getColor() const override;

private:
    Vector3D _position;
    double _intensity;
    Color _color;
};

} // namespace RayTracer

#endif // POINTLIGHT_HPP_
