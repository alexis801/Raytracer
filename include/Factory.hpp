/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace RayTracer {

/**
 * @class Factory
 * @brief Registre de creation d'objets par nom
 */
template <typename T>
class Factory
{
public:
    using Creator = std::function<std::unique_ptr<T>()>;

    /**
     * @brief Enregistre un type dans la factory
     * @param name nom du type
     * @param creator fonction de creation
     */
    void registerType(const std::string &name, Creator creator)
    {
        _creators[name] = std::move(creator);
    }

    /**
     * @brief Cree un objet par son nom
     * @param name nom du type
     */
    std::unique_ptr<T> create(const std::string &name) const
    {
        auto it = _creators.find(name);
        if (it == _creators.end())
            return nullptr;
        return it->second();
    }

    /**
     * @brief Verifie si un type est enregistre
     * @param name nom du type
     */
    bool exists(const std::string &name) const
    {
        return _creators.find(name) != _creators.end();
    }

private:
    std::map<std::string, Creator> _creators;
};

} // namespace RayTracer

#endif // FACTORY_HPP_
