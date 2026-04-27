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
            Color color = computeColor(scene, ray, 0);
            out << color.r << " " << color.g << " "
                << color.b << "\n";
        }
    }
}

Color Renderer::computeColor(const Scene &scene,
    const Ray &ray, int depth) const
{
    auto hit = scene.getClosestHit(ray);

    if (!hit)
        return {0, 0, 0};
    Color surface = computeSurface(scene, *hit);
    if (hit->reflection <= 0 || depth >= MAX_RECURSION_DEPTH)
        return surface;
    Vector3D reflectDir = ray.direction
        - hit->normal * 2.0 * ray.direction.dot(hit->normal);
    Ray reflectRay{
        hit->point + hit->normal * EPSILON,
        reflectDir.normalize()
    };
    Color reflected = computeColor(scene, reflectRay, depth + 1);
    double r = hit->reflection;
    return {
        static_cast<int>(surface.r * (1 - r) + reflected.r * r),
        static_cast<int>(surface.g * (1 - r) + reflected.g * r),
        static_cast<int>(surface.b * (1 - r) + reflected.b * r)
    };
}

Color Renderer::computeSurface(const Scene &scene,
    const HitRecord &hit) const
{
    double intensity = scene.getAmbient();
    for (const auto &light : scene.getLights()) {
        Vector3D lightDir = light->getDirection(hit.point);
        Ray shadowRay{
            hit.point + hit.normal * EPSILON,
            lightDir.normalize()
        };
        auto shadowHit = scene.getClosestHit(shadowRay);
        if (shadowHit
            && shadowHit->distance < light->getDistance(hit.point))
            continue;
        double diffuse = std::max(0.0,
            hit.normal.dot(lightDir.normalize()));
        intensity += scene.getDiffuse()
            * light->getIntensity(hit.point) * diffuse;
    }
    intensity = std::clamp(intensity, 0.0, 1.0);
    return {
        static_cast<int>(hit.color.r * intensity),
        static_cast<int>(hit.color.g * intensity),
        static_cast<int>(hit.color.b * intensity)
    };
}

} // namespace RayTracer
