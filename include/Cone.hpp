/*
** EPITECH PROJECT, 2026
** ray-tracer
** File description:
** Cone.hpp
*/

#ifndef CONE_HPP_
#define CONE_HPP_

#include <string>

#include "IPrimitive.hpp"

namespace RayTracer {
/**
 * @class Cone
 * @brief Forme 3d en Pointe
 */

 class Cone : public IPrimitive {
public:
    Cone(const std::string &axis, const Vector3D apex, double angle,
        const Color color, double height = 0.0);
    ~Cone() override = default;

    // autoriser la copie et deplacement par défaut
    Cone(const Cone &other) = default;
    Cone &operator=(const Cone &other) = default;
    Cone(Cone &&other) = default;
    Cone &operator=(Cone &&other) = default;

    /**
     * @brief Test si le rayonn touche le cone
     * @param ray rayon a tester
     */
    std ::optional<HitRecord> hits(const Ray &ray) const override;

private:
    /**
     * @brief Calcule les coefficients a b c de l'equation quadratique a*t^2 + b*t + c = 0 selon l'axe
     * @param ray Le rayon
     * @param k2 = carré de tan demi angle d'ouverture du cone
     * @param a coefficient a en sortie
     * @param b coefficient b en sortie
     * @param c coefficient c en sortie
     */
    void ComputeQuadraticCoefficients(const Ray &ray, double k2,
        double &a, double &b, double &c) const;

    /**
     * @brief Calcule la normale a la surface du cone
     * @param hitPoint point d'impact dans l'espace
     * @param k2 = carré de tan demi angle d'ouverture du cone
     */
    Vector3D ComputeNormal(const Vector3D &hitPoint, double k2) const;

    /**
     * @brief Verifie qu'un point d'impact est dans la hauteur
     * @param point point d'impact
     */
    bool isInsideHeight(const Vector3D &point) const;

    /**
     * @brief Cherche le root valide le plus proche
     * @param ray rayon
     * @param t1 premier root
     * @param t2 second root
     */
    double findClosestRoot(const Ray &ray, double t1,
        double t2) const;

    std::string _axis; // axe symetrique du cone (x, y ou z)
    Vector3D _apex; // sommet du cone : pointe
    double _angle; // angle ouverture du cone en degrés
    Color _color; // couleur cone
    double _height; // hauteur du cone (0 = infini)
};

} // namespace RayTracer

#endif // CONE_HPP_