/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** types
*/

#include "types.hpp"
#include <cmath>

namespace RayTracer {

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

Vector3D Vector3D::operator*(double scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3D Vector3D::operator/(double scalar) const
{
    return {x / scalar, y / scalar, z / scalar};
}

double Vector3D::dot(const Vector3D &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

double Vector3D::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector3D Vector3D::normalize() const
{
    double len = length();
    if (len == 0)
        return {0, 0, 0};
    return *this / len;
}

} // namespace RayTracer
