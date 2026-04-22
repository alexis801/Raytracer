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

SRC			=	$(shell find $(SRC_DIR) -name '*.cpp')
OBJ			=	$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all:	$(NAME)

LDFLAGS		=	-lconfig++

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean:	clean tests_clean
	$(RM) $(NAME)

re:	fclean all

dev:	CXXFLAGS += -Werror
dev:	re

TEST_SRC	=	$(shell find tests -name '*.cpp')
SRC_NO_MAIN	=	$(filter-out src/main.cpp, $(SRC))

tests_run:	$(NAME)
	$(CXX) $(CXXFLAGS) -o unit_tests $(SRC_NO_MAIN) $(TEST_SRC) --coverage -lcriterion $(LDFLAGS)
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

.PHONY:	all clean fclean re dev tests_run tests_clean doc doc_clean cs
