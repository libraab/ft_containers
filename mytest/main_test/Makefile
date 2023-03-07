# Compiler settings
CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

# Source files
SRCS = main_subject.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build rules
all: ft

ft: $(OBJS)
	@echo "Run ./$@"
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean fclean re

clean:
	@echo "Cleaning up"
	@rm -f $(OBJS) ft

fclean: clean
	@echo "Full Cleaning up"
	@rm -f myprogram

re: fclean all