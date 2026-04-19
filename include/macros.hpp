/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** macros
*/

#ifndef MACROS_HPP_
#define MACROS_HPP_

// Exit codes
#define SUCCESS 0
#define EXIT 84

// PPM
#define PPM_MAGIC "P3"
#define PPM_MAX_COLOR 255

// Math
#define EPSILON 1e-6
#define PI 3.14159265358979323846
#define DEG_TO_RAD(angle) ((angle) * PI / 180.0)
#define RAD_TO_DEG(angle) ((angle) * 180.0 / PI)

// Defaults
#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080
#define DEFAULT_FOV 72.0
#define MAX_RECURSION_DEPTH 5

// Plugins
#define PLUGINS_DIR "./plugins/"
#define PLUGIN_EXT ".so"

// Usage
#define USAGE "USAGE: ./raytracer <SCENE_FILE>\n  SCENE_FILE: scene configuration\n"

#endif // MACROS_HPP_
