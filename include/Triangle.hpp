/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "IPrimitive.hpp"

namespace RayTracer {

/**
 * @class Triangle
 * @brief Forme 3D famille des tétraèdres
 */
class Triangle : public IPrimitive {
    public:
        Triangle(Vector3D center, double radius, Color color,
            double height = 0.0, double reflection = 0.0,
            double transparency = 0.0, double refraction = 1.0,
            double specular = 0.0, double shininess = 0.0);
        ~Triangle() override = default;

        Triangle(const Triangle &other) = default;
        Triangle &operator=(const Triangle &other) = default;
        Triangle(Triangle &&other) = default;
        Triangle &operator=(Triangle &&other) = default;

        /**
        * @brief Teste si un rayon touche le triangle
        * @param ray rayon a tester
        */
        std::optional<HitRecord> hits(const Ray &ray) const override;

    private:
        Vector3D _center;
        double _radius;
        Color _color;
        double _height;
        double _reflection;
        double _transparency;
        double _refraction;
        double _specular;
        double _shininess;
};

}
#endif /* !TRIANGLE_HPP_ */
