NAME = ft
CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98


all: $(NAME) fclean

${NAME}:
	${CC} ${FLAGS} *.cpp -o $@

fclean:
	rm -rf $(NAME) $(OUTPUT)

re :
	fclean all

.PHONY: all $(NAME) fclean re
