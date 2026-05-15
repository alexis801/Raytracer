/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_


#include "IPrimitive.hpp"
#include "Texture.hpp"
#include <memory>

namespace RayTracer {

/**
 * @class Cylinder
 * @brief Forme 3D ronde
 */
class Cylinder : public IPrimitive {
    public:
        Cylinder(Vector3D center, double radius, Color color,
            double height = 0.0, double reflection = 0.0,
            double transparency = 0.0, double refraction = 1.0,
            double specular = 0.0, double shininess = 0.0,
            std::shared_ptr<Texture> texture = nullptr);
        ~Cylinder() override = default;

        Cylinder(const Cylinder &other) = default;
        Cylinder &operator=(const Cylinder &other) = default;
        Cylinder(Cylinder &&other) = default;
        Cylinder &operator=(Cylinder &&other) = default;

        /**
         * @brief Calcule la distance d'intersection rayon/cylindre
         * @param ray rayon a tester
         */
        std::optional<double> quadratic(const Ray &ray) const;

        /**
         * @brief Teste si un rayon touche le cylindre
         * @param ray rayon a tester
         */
        std::optional<HitRecord> hits(const Ray &ray) const override;

    private:
        /**
         * @brief Verifie qu'un t est valide (positif et dans la hauteur)
         * @param ray rayon
         * @param t parametre a tester
         */
        bool isValid(const Ray &ray, double t) const;

        Vector3D _center;
        double _radius;
        Color _color;
        double _height;
        double _reflection;
        double _transparency;
        double _refraction;
        double _specular;
        double _shininess;
        std::shared_ptr<Texture> _texture;
};

} // namespace RayTracer


#endif /* !CYLINDER_HPP_ */
