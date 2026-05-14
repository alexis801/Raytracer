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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


void updateTexture(sf::Texture &texture, const std::vector<RayTracer::Color> &framebuffer, int width, int height)
{
    std::vector<sf::Uint8> pixels(width * height * 4);
    for (int i = 0; i < width * height; ++i) {
        pixels[i * 4]     = framebuffer[i].r;
        pixels[i * 4 + 1] = framebuffer[i].g;
        pixels[i * 4 + 2] = framebuffer[i].b;
        pixels[i * 4 + 3] = 255;
    }
    texture.update(pixels.data());
}

void runInteractiveMode(RayTracer::Scene &scene, RayTracer::Camera &camera, RayTracer::Renderer &renderer)
{
    int width = camera.getWidth();
    int height = camera.getHeight();

    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer ");
    sf::Texture texture;
    texture.create(width, height);
    sf::Sprite sprite(texture);
    std::vector<RayTracer::Color> framebuffer(width * height);
    bool redraw = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
                    camera.moveZ(10.0);
                    redraw = true;
                }
                if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Dash) {
                    camera.moveZ(-10.0);
                    redraw = true;
                }
            }
        }
        if (redraw) {
            renderer.renderToBuffer(scene, camera, framebuffer, 1);
            updateTexture(texture, framebuffer, width, height);
            redraw = false;
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) return 84;

    try {
        RayTracer::SceneParser parser;
        RayTracer::Scene scene;
        RayTracer::Camera camera;
        parser.parse(argv[1], scene, camera);
        RayTracer::Renderer renderer;
        runInteractiveMode(scene, camera, renderer);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}