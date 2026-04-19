/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** main
*/

#include "macros.hpp"
#include "Renderer.hpp"
#include "SceneParser.hpp"
#include <iostream>
#include <stdexcept>

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
    try {
        RayTracer::Scene scene;
        RayTracer::Camera camera;
        RayTracer::SceneParser parser;
        parser.parse(sceneFile, scene, camera);
        RayTracer::Renderer renderer;
        renderer.render(scene, camera, std::cout);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT;
    }
    return SUCCESS;
}
