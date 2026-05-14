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

    protected:
    private:
};

}
#endif /* !TRIANGLE_HPP_ */
