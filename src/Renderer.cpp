/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "macros.hpp"
#include <algorithm>

namespace RayTracer {

void Renderer::render(const Scene &scene, const Camera &camera,
    std::ostream &out) const
{
    int width = camera.getWidth();
    int height = camera.getHeight();

    out << PPM_MAGIC << "\n";
    out << width << " " << height << "\n";
    out << PPM_MAX_COLOR << "\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Ray ray = camera.generateRay(x, y);
            Color color = computeColor(scene, ray);
            out << color.r << " " << color.g << " "
                << color.b << "\n";
        }
    }
}

Color Renderer::computeColor(const Scene &scene,
    const Ray &ray) const
{
    auto hit = scene.getClosestHit(ray);

    if (!hit)
        return {0, 0, 0};
    double intensity = 0.0;
    for (const auto &light : scene.getLights()) {
        double lightIntensity = light->getIntensity(hit->point);
        Vector3D lightDir = light->getDirection(hit->point);
        double diffuse = std::max(0.0,
            hit->normal.dot(lightDir.normalize()));
        intensity += lightIntensity * diffuse;
    }
    intensity = std::clamp(intensity, 0.0, 1.0);
    return {
        static_cast<int>(hit->color.r * intensity),
        static_cast<int>(hit->color.g * intensity),
        static_cast<int>(hit->color.b * intensity)
    };
}

} // namespace RayTracer
