/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DirectionalLight
*/

#ifndef DIRECTIONALLIGHT_HPP_
#define DIRECTIONALLIGHT_HPP_

#include "ILight.hpp"

namespace RayTracer {

/**
 * @class DirectionalLight
 * @brief Lumiere qui provient d'une direction
 */
class DirectionalLight : public ILight {
public:
    DirectionalLight(Vector3D direction, double intensity);
    ~DirectionalLight() override = default;

    DirectionalLight(const DirectionalLight &other) = default;
    DirectionalLight &operator=(const DirectionalLight &other) = default;
    DirectionalLight(DirectionalLight &&other) = default;
    DirectionalLight &operator=(DirectionalLight &&other) = default;

    /**
     * @brief Direction vers la lumiere
     * @param point point eclaire
     */
    Vector3D getDirection(const Vector3D &point) const override;

    /**
     * @brief Intensite de la lumiere
     * @param point point eclaire
     */
    double getIntensity(const Vector3D &point) const override;

    /**
     * @brief Distance a la lumiere (infinie pour directionnelle)
     * @param point point eclaire
     */
    double getDistance(const Vector3D &point) const override;

private:
    Vector3D _direction;
    double _intensity;
};

} // namespace RayTracer

#endif // DIRECTIONALLIGHT_HPP_
