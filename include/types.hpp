/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** types de base
*/

#ifndef TYPES_HPP_
#define TYPES_HPP_

namespace RayTracer {

/**
 * @class Vector3D
 * @brief Vecteur 3D
 */
class Vector3D {
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vector3D() = default;
    Vector3D(double x, double y, double z);
    ~Vector3D() = default;

    Vector3D(const Vector3D &other) = default;
    Vector3D &operator=(const Vector3D &other) = default;
    Vector3D(Vector3D &&other) = default;
    Vector3D &operator=(Vector3D &&other) = default;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;
    double dot(const Vector3D &other) const;
    Vector3D cross(const Vector3D &other) const;
    double length() const;
    Vector3D normalize() const;
};

/**
 * @brief Couleur RGB
 */
struct Color {
    int r = 0;
    int g = 0;
    int b = 0;
};

/**
 * @brief Rayon
 */
struct Ray {
    Vector3D origin;
    Vector3D direction;
};

/**
 * @brief Resultat d'intersection
 */
struct HitRecord {
    Vector3D point;
    Vector3D normal;
    double distance = 0;
    Color color;
};

} // namespace RayTracer

#endif // TYPES_HPP_
