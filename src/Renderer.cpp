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

void Renderer::render(const Scene &scene, const Camera &camera, std::ostream &out,
    int numThreads, int antiAliasing) const
{
    int imageWidth = camera.getWidth();
    int imageHeight = camera.getHeight();

    std::vector<Color> framebuffer(imageWidth * imageHeight);
    std::vector<std::thread> threads;
    if (numThreads <= 0)
        numThreads = 1;
    int rowsPerThread = imageHeight / numThreads;
    for (int i = 0; i < numThreads; i++) {
        int rowStart = i * rowsPerThread;
        int rowEnd = (i == numThreads - 1) ? imageHeight : (i + 1) * rowsPerThread;
        threads.emplace_back(&Renderer::renderPart, this, 
            std::ref(scene), std::ref(camera), std::ref(framebuffer), rowStart, rowEnd, antiAliasing);
    }
    for (auto &t : threads) {
        t.join();
    }
    out << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
    for (const auto &pixel : framebuffer) {
        out << pixel.r << " " << pixel.g << " " << pixel.b << "\n";
    }
}

void Renderer::renderPart(const Scene &scene, const Camera &camera, 
    std::vector<Color> &framebuffer, int rowStart, int rowEnd, int antiAliasing) const
{
    int imageWidth = camera.getWidth();
    double Pixielsize = 1.0 / antiAliasing;

    for (int y = rowStart; y < rowEnd; y++) {
        for (int x = 0; x < imageWidth; x++) {
            double totalRed = 0;
            double totalGreen = 0;
            double totalBlue = 0;
            for (int sy = 0; sy < antiAliasing; sy++) {
                for (int sx = 0; sx < antiAliasing; sx++) {
                    double offsetX = x + (sx + 0.5) * Pixielsize;
                    double offsetY = y + (sy + 0.5) * Pixielsize;
                    Ray ray = camera.generateRay(offsetX, offsetY);
                    Color subColor = computeColor(scene, ray, 0);
                    totalRed += subColor.r;
                    totalGreen += subColor.g;
                    totalBlue += subColor.b;
                }
            }
            int numSamples = antiAliasing * antiAliasing;
            framebuffer[y * imageWidth + x] = {
                static_cast<int>(totalRed / numSamples),
                static_cast<int>(totalGreen / numSamples),
                static_cast<int>(totalBlue / numSamples)
            };
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
