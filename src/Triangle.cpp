/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace RayTracer {

Triangle::Triangle(Vector3D center, double radius, Color color,
    double height, double reflection, double transparency,
    double refraction, double specular, double shininess)
    : _center(center), _radius(radius), _color(color),
      _height(height), _reflection(reflection),
      _transparency(transparency), _refraction(refraction),
      _specular(specular), _shininess(shininess)
{
}

}
