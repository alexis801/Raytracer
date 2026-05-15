##
## EPITECH PROJECT, 2026
## Raytracer
## File description:
## Makefile
##

NAME		=	raytracer

CXX			=	clang++
CXXFLAGS	=	-Wall -Wextra -std=c++20 -iquote ./include

SRC_DIR		=	src
OBJ_DIR		=	obj
PLUGIN_DIR	=	plugins

CORE_SRC	=	src/main.cpp src/Scene.cpp src/types.cpp \
				src/Camera.cpp src/Renderer.cpp \
				src/SceneParser.cpp src/SceneNode.cpp \
				src/PluginManager.cpp
CORE_OBJ	=	$(CORE_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

PLUGIN_NAMES	=	raytracer_sphere raytracer_plane \
					raytracer_cone raytracer_cylinder \
					raytracer_triangle \
					raytracer_pointlight raytracer_directionallight
PLUGINS		=	$(PLUGIN_NAMES:%=$(PLUGIN_DIR)/%.so)

LDFLAGS		=	-lconfig++ -ldl -lsfml-graphics -lsfml-window -lsfml-system

all:	deps $(NAME) $(PLUGINS)

deps:
	@echo '#include <libconfig.h++>' | $(CXX) -E -x c++ - -o /dev/null 2>/dev/null \
		|| (apt-get update && apt-get install -y libconfig++-dev) 2>/dev/null \
		|| (dnf install -y libconfig-devel) 2>/dev/null
	@echo '#include <SFML/Graphics.hpp>' | $(CXX) -E -x c++ - -o /dev/null 2>/dev/null \
		|| (apt-get update && apt-get install -y libsfml-dev) 2>/dev/null \
		|| (dnf install -y SFML-devel) 2>/dev/null

$(NAME):	$(CORE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PLUGIN_DIR)/raytracer_sphere.so: src/Sphere.cpp src/types.cpp src/Texture.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++ -lsfml-graphics -lsfml-system

$(PLUGIN_DIR)/raytracer_plane.so: src/Plane.cpp src/types.cpp src/Texture.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++ -lsfml-graphics -lsfml-system

$(PLUGIN_DIR)/raytracer_cone.so: src/Cone.cpp src/types.cpp src/Texture.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++ -lsfml-graphics -lsfml-system

$(PLUGIN_DIR)/raytracer_cylinder.so: src/Cylinder.cpp src/types.cpp src/Texture.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++ -lsfml-graphics -lsfml-system

$(PLUGIN_DIR)/raytracer_pointlight.so: src/PointLight.cpp src/types.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++

$(PLUGIN_DIR)/raytracer_directionallight.so: src/DirectionalLight.cpp src/types.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++

$(PLUGIN_DIR)/raytracer_triangle.so: src/Triangle.cpp src/types.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -DPLUGIN_BUILD -shared -fPIC -o $@ $^ -lconfig++


clean:
	$(RM) -r $(OBJ_DIR)

fclean:	clean tests_clean
	$(RM) $(NAME)
	$(RM) -r $(PLUGIN_DIR)

re:	fclean all

dev:	CXXFLAGS += -Werror
dev:	re

TEST_SRC	=	$(shell find tests -name '*.cpp')
CORE_NO_MAIN=	$(filter-out src/main.cpp, $(CORE_SRC))
PLUGIN_SRC	=	src/Sphere.cpp src/Plane.cpp src/Cone.cpp \
				src/Cylinder.cpp src/PointLight.cpp \
				src/Triangle.cpp \
				src/DirectionalLight.cpp \
				src/Texture.cpp

tests_run:	$(NAME)
	$(CXX) $(CXXFLAGS) -o unit_tests $(CORE_NO_MAIN) $(PLUGIN_SRC) $(TEST_SRC) --coverage -lcriterion $(LDFLAGS)
	./unit_tests
	gcovr -r . --exclude tests/ --gcov-executable "llvm-cov gcov"

tests_clean:
	$(RM) unit_tests
	$(RM) -r *.gc* **/*.gc*

docs:
	doxygen Doxyfile
	xdg-open docs/html/index.html

doc_clean:
	$(RM) -r docs

.PHONY:	all deps clean fclean re dev tests_run tests_clean doc doc_clean cs
