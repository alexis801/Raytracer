/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <stdexcept>
#include <dlfcn.h>

namespace RayTracer {

/**
 * @class DLLoader
 * @brief Charge une librairie dynamique (.so)
 */
class DLLoader {
public:
    DLLoader(const std::string &path)
        : _handle(dlopen(path.c_str(), RTLD_LAZY))
    {
        if (!_handle)
            throw std::runtime_error(
                "DLLoader: " + std::string(dlerror()));
    }

    ~DLLoader()
    {
        if (_handle)
            dlclose(_handle);
    }

    DLLoader(const DLLoader &other) = delete;
    DLLoader &operator=(const DLLoader &other) = delete;

    DLLoader(DLLoader &&other) noexcept
        : _handle(other._handle)
    {
        other._handle = nullptr;
    }

    DLLoader &operator=(DLLoader &&other) noexcept
    {
        if (_handle)
            dlclose(_handle);
        _handle = other._handle;
        other._handle = nullptr;
        return *this;
    }

    /**
     * @brief Recupere un symbole dans la lib
     * @param name nom du symbole
     */
    template <typename T>
    T getSymbol(const std::string &name) const
    {
        void *sym = dlsym(_handle, name.c_str());
        if (!sym)
            throw std::runtime_error(
                "DLLoader: " + std::string(dlerror()));
        return reinterpret_cast<T>(sym);
    }

private:
    void *_handle;
};

} // namespace RayTracer

#endif // DLLOADER_HPP_
