/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "IPrimitive.hpp"
#include "ILight.hpp"
#include <memory>
#include <vector>

namespace RayTracer {

/**
 * @class Scene
 * @brief Contient les objets et lumieres
 */
class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene &other) = delete;
    Scene &operator=(const Scene &other) = delete;
    Scene(Scene &&other) = default;
    Scene &operator=(Scene &&other) = default;

    /**
     * @brief Ajoute une forme a la scene
     * @param primitive forme a ajouter
     */
    void addPrimitive(std::unique_ptr<IPrimitive> primitive);

    /**
     * @brief Ajoute une lumiere a la scene
     * @param light lumiere a ajouter
     */
    void addLight(std::unique_ptr<ILight> light);

    /**
     * @brief Trouve l'objet le plus proche touche par un rayon
     * @param ray rayon a tester
     */
    std::optional<HitRecord> getClosestHit(const Ray &ray) const;

    /**
     * @brief Renvoie les lumieres de la scene
     */
    const std::vector<std::unique_ptr<ILight>> &getLights() const;

private:
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::vector<std::unique_ptr<ILight>> _lights;
};

} // namespace RayTracer

#endif // SCENE_HPP_
