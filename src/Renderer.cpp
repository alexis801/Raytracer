/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"
#include "macros.hpp"
#include <algorithm>
#include <cmath>

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
    if (depth >= MAX_RECURSION_DEPTH)
        return surface;
    Color reflected = computeReflection(scene, ray, *hit, depth);
    Color refracted = computeRefraction(scene, ray, *hit, depth);
    double refl = hit->reflection;
    double trans = hit->transparency;
    double surf = 1.0 - refl - trans;
    return {
        static_cast<int>(surface.r * surf
            + reflected.r * refl + refracted.r * trans),
        static_cast<int>(surface.g * surf
            + reflected.g * refl + refracted.g * trans),
        static_cast<int>(surface.b * surf
            + reflected.b * refl + refracted.b * trans)
    };
}

Color Renderer::computeReflection(const Scene &scene,
    const Ray &ray, const HitRecord &hit, int depth) const
{
    if (hit.reflection <= 0)
        return {0, 0, 0};
    Vector3D reflectDir = ray.direction
        - hit.normal * 2.0 * ray.direction.dot(hit.normal);
    Ray reflectRay{
        hit.point + hit.normal * EPSILON,
        reflectDir.normalize()
    };
    return computeColor(scene, reflectRay, depth + 1);
}

Color Renderer::computeRefraction(const Scene &scene,
    const Ray &ray, const HitRecord &hit, int depth) const
{
    if (hit.transparency <= 0)
        return {0, 0, 0};
    double cosI = ray.direction.dot(hit.normal) * -1;
    Vector3D normal = hit.normal;
    double eta = 1.0 / hit.refraction;
    if (cosI < 0) {
        cosI = -cosI;
        normal = normal * -1;
        eta = hit.refraction;
    }
    double sin2T = eta * eta * (1.0 - cosI * cosI);
    if (sin2T > 1.0)
        return computeReflection(scene, ray, hit, depth);
    double cosT = std::sqrt(1.0 - sin2T);
    Vector3D refractDir = ray.direction * eta
        + normal * (eta * cosI - cosT);
    Ray refractRay{
        hit.point - normal * EPSILON,
        refractDir.normalize()
    };
    return computeColor(scene, refractRay, depth + 1);
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
