/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "IPrimitive.hpp"
#include "types.hpp"

namespace RayTracer {

/**
 * @class Triangle
 * @brief Représente un triangle 3D défini par 3 sommets
 */
class Triangle : public IPrimitive {
public:
    /**
     * @brief Constructeur d'un triangle
     * @param v0 Premier sommet
     * @param v1 Deuxième sommet
     * @param v2 Troisième sommet
     * @param color Couleur du triangle
     * @param reflection Coefficient de réflexion
     * @param transparency Coefficient de transparence
     * @param refraction Indice de réfraction
     * @param specular Coefficient spéculaire
     * @param shininess Brillance
     */
    Triangle(
        Vector3D v0, Vector3D v1, Vector3D v2,
        Color color,
        double reflection = 0.0,
        double transparency = 0.0,
        double refraction = 1.0,
        double specular = 0.0,
        double shininess = 0.0
    );

    ~Triangle() override = default;

    Triangle(const Triangle &other) = default;
    Triangle &operator=(const Triangle &other) = default;
    Triangle(Triangle &&other) = default;
    Triangle &operator=(Triangle &&other) = default;

    /**
     * @brief Teste si un rayon touche le triangle.
     * @param ray Rayon à tester.
     * @return HitRecord si intersection, std::nullopt sinon.
     */
    std::optional<HitRecord> hits(const Ray &ray) const override;

private:
    Vector3D _v0;  // premier sommet
    Vector3D _v1;  // deuxième sommet
    Vector3D _v2;  // troisième sommets
    Vector3D _normal;  // Normale du triangle (calculée dans le constructeur)
    Color _color;
    double _reflection;
    double _transparency;
    double _refraction;
    double _specular;
    double _shininess;

    bool computeIntersection(const Ray &ray, double &u, double &v, double &t) const;
    /**
     * @brief calcule la normale du triangle à partir des 3 sommets
     */
    Vector3D computeNormal() const;
};

} // namespace RayTracer

#endif /* !TRIANGLE_HPP_ */
