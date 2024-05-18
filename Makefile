SRC	=	src/Orca.cpp \
		src/FileElement.cpp \
		src/test.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME		=	orca

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -g

SFMLFLAGS	=	-lsfml-graphics -lsfml-system -lsfml-window

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(SFMLFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all

.PHONY: all clean fclean re
