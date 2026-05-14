/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "types.hpp"

namespace RayTracer {

/**
 * @class Camera
 * @brief Point de vue de la scene
 */
class Camera {
public:
    Camera() = default;
    Camera(int width, int height, Vector3D position,
        Vector3D rotation, double fov);
    ~Camera() = default;

    Camera(const Camera &other) = default;
    Camera &operator=(const Camera &other) = default;
    Camera(Camera &&other) = default;
    Camera &operator=(Camera &&other) = default;

    /**
     * @brief Genere un rayon pour un pixel
     * @param x colonne du pixel
     * @param y ligne du pixel
     */
    Ray generateRay(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    void moveZ(double offset);

private:
    int _width = 1920;
    int _height = 1080;
    Vector3D _position;
    Vector3D _rotation;
    double _fov = 72.0;
};

} // namespace RayTracer

#endif // CAMERA_HPP_
