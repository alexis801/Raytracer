/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** macros
*/

#ifndef MACROS_HPP_
#define MACROS_HPP_

// Exit codes
constexpr int SUCCESS = 0;
constexpr int EXIT = 84;

// PPM
constexpr const char *PPM_MAGIC = "P3";
constexpr int PPM_MAX_COLOR = 255;

// Math
constexpr double EPSILON = 1e-6;
constexpr double PI = 3.14159265358979323846;
#define DEG_TO_RAD(angle) ((angle) * PI / 180.0)
#define RAD_TO_DEG(angle) ((angle) * 180.0 / PI)

// Defaults
constexpr int DEFAULT_WIDTH = 1920;
constexpr int DEFAULT_HEIGHT = 1080;
constexpr double DEFAULT_FOV = 72.0;
constexpr int MAX_RECURSION_DEPTH = 5;

// Plugins
constexpr const char *PLUGINS_DIR = "./plugins/";
constexpr const char *PLUGIN_EXT = ".so";

// Usage
constexpr const char *USAGE =
    "USAGE: ./raytracer <SCENE_FILE>\n  SCENE_FILE: scene configuration\n";

#endif // MACROS_HPP_
