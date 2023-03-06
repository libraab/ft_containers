NAME = std ft
CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98
OUTPUT = $(NAME:=.output)

all: $(NAME) diff fclean

${NAME}:
	${CC} ${FLAGS} -DTESTED_NAMESPACE=$@ *.cpp -o $@
	time ./$@ > $@.output

diff: ${NAME}
	diff $(OUTPUT)

fclean:
	rm -rf $(NAME) $(OUTPUT)

re : 		fclean all

.PHONY: all $(NAME) diff fclean re
