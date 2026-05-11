/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "IPrimitive.hpp"

namespace RayTracer {

/**
 * @class Sphere
 * @brief Forme 3D ronde
 */
class Sphere : public IPrimitive {
public:
    Sphere(Vector3D center, double radius, Color color,
        double reflection = 0.0, double transparency = 0.0,
        double refraction = 1.0, double specular = 0.0,
        double shininess = 0.0);
    ~Sphere() override = default;

    Sphere(const Sphere &other) = default;
    Sphere &operator=(const Sphere &other) = default;
    Sphere(Sphere &&other) = default;
    Sphere &operator=(Sphere &&other) = default;

    /**
     * @brief Teste si un rayon touche la sphere
     * @param ray rayon a tester
     */
    std::optional<HitRecord> hits(const Ray &ray) const override;

private:
    Vector3D _center;
    double _radius;
    Color _color;
    double _reflection;
    double _transparency;
    double _refraction;
    double _specular;
    double _shininess;
};

} // namespace RayTracer

#endif // SPHERE_HPP_
