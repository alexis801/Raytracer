/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** main
*/

#include "macros.hpp"
#include "Renderer.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << USAGE;
        return EXIT;
    }
    std::string sceneFile = argv[1];
    if (sceneFile == "--help" || sceneFile == "-h") {
        std::cout << USAGE;
        return SUCCESS;
    }
    RayTracer::Scene scene;
    RayTracer::Camera camera;
    RayTracer::Renderer renderer;
    renderer.render(scene, camera, std::cout);
    return SUCCESS;
}
