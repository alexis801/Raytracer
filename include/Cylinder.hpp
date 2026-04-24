/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_


#include "IPrimitive.hpp"

namespace RayTracer {

/**
 * @class Cylinder
 * @brief Forme 3D ronde
 */
class Cylinder : public IPrimitive {
    public:
        Cylinder(Vector3D center, double radius, Color color);
        ~Cylinder() override = default;
    
        Cylinder(const Cylinder &other) = default;
        Cylinder &operator=(const Cylinder &other) = default;
        Cylinder(Cylinder &&other) = default;
        Cylinder &operator=(Cylinder &&other) = default;
    
        /**
         * @brief Teste si un rayon touche la Cylinder
         * @param ray rayon a tester
         */
        std::optional<HitRecord> hits(const Ray &ray) const override;
    
    private:
        Vector3D _center;
        double _radius;
        Color _color;
};

} // namespace RayTracer


#endif /* !CYLINDER_HPP_ */
