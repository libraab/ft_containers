NAME = std ft
CC = clang++
FLAGS = -Wall -Wextra -Werror -std=c++98
OUTPUT = $(NAME:=.output)
SOURCES = 	main.cpp \
			def.cpp \
			default_copy.cpp \
			list_copy.cpp \
			relational_ope_list.cpp \
			relational_ope.cpp

# Generate object file names from source file names
OBJS = $(SOURCES:.cpp=.o)

all: $(NAME)

# Link object files to create output files
$(NAME): $(OBJS)
	@${CC} ${FLAGS} -DTESTED_NAMESPACE=$@ $^ -o $@
	@printf "RUNNING $@ ✅\n"
	@printf "➖➖➖➖➖➖➖➖"
	@time ./$@ > $@.output
	@printf "➖➖➖➖➖➖➖➖"
	@echo "\n"

# Compile each source file into an object file
%.o: %.cpp
	@printf "Compiling -> $<"
	@${CC} ${FLAGS} -c $< -o $@
	@echo " ✅"

diff: $(OUTPUT)
	@echo "Comparing output files ..."
	@diff $(OUTPUT)
	@if [ $$? -eq 0 ]; then \
		echo "The output files are identical 👍"; \
	else \
		echo "The output files are different 👎"; \
	fi

fclean:
	@echo "Cleaning up...💨 🧹🗑️"
	@rm -rf $(NAME) $(OUTPUT) $(OBJS)

re: fclean all

.PHONY: all $(NAME) diff fclean re