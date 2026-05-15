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
                    double coordX = x + (sx + 0.5) * Pixielsize;
                    double coordY = y + (sy + 0.5) * Pixielsize;
                    Ray ray = camera.generateRay(coordX, coordY);
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
    Color surface = computeSurface(scene, ray, *hit);
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

void Renderer::accumulateLight(const Scene &scene,
    const ILight &light, const Ray &ray, const HitRecord &hit,
    double diffRgb[3], double specRgb[3]) const
{
    Vector3D lightDir = light.getDirection(hit.point);
    Vector3D L = lightDir.normalize();
    Ray shadowRay{hit.point + hit.normal * EPSILON, L};
    auto shadowHit = scene.getClosestHit(shadowRay);

    if (shadowHit
        && shadowHit->distance < light.getDistance(hit.point))
        return;

    // Composante diffuse (Lambert)
    double diffuse = std::max(0.0, hit.normal.dot(L));
    double diffContrib = scene.getDiffuse()
        * light.getIntensity(hit.point) * diffuse;
    Color lc = light.getColor();
    diffRgb[0] += diffContrib * (lc.r / 255.0);
    diffRgb[1] += diffContrib * (lc.g / 255.0);
    diffRgb[2] += diffContrib * (lc.b / 255.0);

    if (hit.specular <= 0.0 || diffuse <= 0.0)
        return;
    // R = 2 * (N . L) * N - L : direction de la lumiere reflechie
    Vector3D R = hit.normal * 2.0 * hit.normal.dot(L) - L;
    // V : direction du point vers la camera oppose au rayon
    Vector3D V = (ray.direction * -1.0).normalize();
    double RdotV = std::max(0.0, R.dot(V));
    double shininess = hit.shininess > 0.0 ? hit.shininess : 32.0;
    double specFactor = std::pow(RdotV, shininess)
        * hit.specular * light.getIntensity(hit.point);
    // Le reflet prend la couleur de la lumiere
    specRgb[0] += specFactor * (lc.r / 255.0);
    specRgb[1] += specFactor * (lc.g / 255.0);
    specRgb[2] += specFactor * (lc.b / 255.0);
}

Color Renderer::computeSurface(const Scene &scene,
    const Ray &ray, const HitRecord &hit) const
{
    double diffRgb[3] = {scene.getAmbient(), scene.getAmbient(), scene.getAmbient()};
    double specRgb[3] = {0.0, 0.0, 0.0};

    for (const auto &light : scene.getLights())
        accumulateLight(scene, *light, ray, hit, diffRgb, specRgb);
    return {
    std::clamp(static_cast<int>(hit.color.r * std::clamp(diffRgb[0], 0.0, 1.0)
        + 255.0 * std::clamp(specRgb[0], 0.0, 1.0)), 0, 255),
    std::clamp(static_cast<int>(hit.color.g * std::clamp(diffRgb[1], 0.0, 1.0)
        + 255.0 * std::clamp(specRgb[1], 0.0, 1.0)), 0, 255),
    std::clamp(static_cast<int>(hit.color.b * std::clamp(diffRgb[2], 0.0, 1.0)
        + 255.0 * std::clamp(specRgb[2], 0.0, 1.0)), 0, 255)
    };
}

void Renderer::renderToBuffer(const Scene &scene, const Camera &camera, 
    std::vector<Color> &framebuffer, int antiAliasing) const
{
    int imageWidth = camera.getWidth();
    int imageHeight = camera.getHeight();
    
    if (framebuffer.size() != static_cast<size_t>(imageWidth * imageHeight))
        framebuffer.resize(imageWidth * imageHeight);
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 1;
    std::vector<std::thread> threads;
    int rowsPerThread = imageHeight / numThreads;
    for (unsigned int i = 0; i < numThreads; i++) {
        int rowStart = i * rowsPerThread;
        int rowEnd = (i == numThreads - 1) ? imageHeight : (i + 1) * rowsPerThread;
        threads.emplace_back(&Renderer::renderPart, this, 
            std::ref(scene), std::ref(camera), std::ref(framebuffer), 
            rowStart, rowEnd, antiAliasing);
    }
    for (auto &t : threads) {
        t.join();
    }
}
} // namespace RayTracer
