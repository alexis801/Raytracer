/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "Scene.hpp"
#include "Camera.hpp"
#include <ostream>

namespace RayTracer {

/**
 * @class Renderer
 * @brief Moteur de rendu par lancer de rayons
 */
class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    Renderer(const Renderer &other) = delete;
    Renderer &operator=(const Renderer &other) = delete;
    Renderer(Renderer &&other) = delete;
    Renderer &operator=(Renderer &&other) = delete;

    /**
     * @brief Lance le rendu et ecrit l'image en PPM
     * @param scene scene a rendre
     * @param camera point de vue
     * @param out flux de sortie
     */
    void render(const Scene &scene, const Camera &camera,
        std::ostream &out) const;

private:
    /**
     * @brief Calcule la couleur d'un rayon
     * @param scene scene a tester
     * @param ray rayon lance
     * @param depth profondeur de recursion
     */
    Color computeColor(const Scene &scene, const Ray &ray,
        int depth = 0) const;

    /**
     * @brief Calcule la couleur de surface sans reflexion
     * @param scene scene a tester
     * @param hit point d'intersection
     */
    Color computeSurface(const Scene &scene,
        const HitRecord &hit) const;

    /**
     * @brief Calcule la couleur reflechie
     * @param scene scene a tester
     * @param ray rayon incident
     * @param hit point d'intersection
     * @param depth profondeur de recursion
     */
    Color computeReflection(const Scene &scene,
        const Ray &ray, const HitRecord &hit,
        int depth) const;

    /**
     * @brief Calcule la couleur refractee
     * @param scene scene a tester
     * @param ray rayon incident
     * @param hit point d'intersection
     * @param depth profondeur de recursion
     */
    Color computeRefraction(const Scene &scene,
        const Ray &ray, const HitRecord &hit,
        int depth) const;
};

} // namespace RayTracer

#endif // RENDERER_HPP_
