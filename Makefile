NAME = ft_containers

#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
# ███████╗    ██╗    ██╗         ███████╗    ███████╗  #
# ██╔════╝    ██║    ██║         ██╔════╝    ██╔════╝  #
# █████╗      ██║    ██║         █████╗      ███████╗  #
# ██╔══╝      ██║    ██║         ██╔══╝      ╚════██║  #
# ██║         ██║    ███████╗    ███████╗    ███████║  #
# ╚═╝         ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝  #
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
SRCS_FILES =	main.cpp 

OBJS			= $(SRCS_FILES:.cpp=.o)
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
#  ██████╗     ██████╗     ███╗   ███╗    ██████╗     ██╗    ██╗      #
# ██╔════╝    ██╔═══██╗    ████╗ ████║    ██╔══██╗    ██║    ██║      #
# ██║         ██║   ██║    ██╔████╔██║    ██████╔╝    ██║    ██║      #
# ██║         ██║   ██║    ██║╚██╔╝██║    ██╔═══╝     ██║    ██║      #
# ╚██████╗    ╚██████╔╝    ██║ ╚═╝ ██║    ██║         ██║    ███████╗ #
#  ╚═════╝     ╚═════╝     ╚═╝     ╚═╝    ╚═╝         ╚═╝    ╚══════╝ #
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
COMP		= clang++
FLAGS	  	= -Wall -Wextra -Werror -std=c++98 #-D STD=1 -g -fsanitize=address

RM			= rm -rf
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
# ██████╗     ██╗   ██╗    ██╗         ███████╗    ███████╗ #
# ██╔══██╗    ██║   ██║    ██║         ██╔════╝    ██╔════╝ #
# ██████╔╝    ██║   ██║    ██║         █████╗      ███████╗ #
# ██╔══██╗    ██║   ██║    ██║         ██╔══╝      ╚════██║ #
# ██║  ██║    ╚██████╔╝    ███████╗    ███████╗    ███████║ #
# ╚═╝  ╚═╝     ╚═════╝     ╚══════╝    ╚══════╝    ╚══════╝ #
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
$(NAME):	$(OBJS)
			@$(COMP) $(FLAGS) $(OBJS) -o $(NAME)
			@printf "➖➖➖➖➖➖➖➖➖➖➖➖➖                         \n"
			@printf $(green)
			@printf "CONTAINERS'S FILES COMPILED ✅\n"
			@printf "➖➖➖➖➖➖➖➖➖➖➖➖➖                         \n"
			@printf $(reset)

all:		$(NAME)

%.o: %.cpp
			@printf $(green)
			@printf "Generating objects...%-33.33s    \r" $@
			@$(COMP) -o $@ -c $< $(FLAGS)
			@printf $(reset)

re: 		fclean all


clean:
			@$(RM) $(OBJS)
			@printf $(yellow)
			@printf "Object files have been deleted 🗑 \n"
			@printf $(reset)

fclean:		clean
			@$(RM) $(NAME)
			@printf $(cyan)
			@printf "Executable file has been deleted 🗑 \n"
			@printf $(red)
			@printf "✨ Your folder is now clean ✨\n"
			@printf $(reset)

run		: re
		./$(NAME) 8080 123

.PHONY: 	all clean fclean re
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
#  ██████╗     ██████╗     ██╗          ██████╗     ██████╗   #
# ██╔════╝    ██╔═══██╗    ██║         ██╔═══██╗    ██╔══██╗  #
# ██║         ██║   ██║    ██║         ██║   ██║    ██████╔╝  #
# ██║         ██║   ██║    ██║         ██║   ██║    ██╔══██╗  #
# ╚██████╗    ╚██████╔╝    ███████╗    ╚██████╔╝    ██║  ██║  #
#  ╚═════╝     ╚═════╝     ╚══════╝     ╚═════╝     ╚═╝  ╚═╝  #
#➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖ #
black 				=	"[1;30m"
red 				=	"[1;31m"
green 				=	"[1;32m"
yellow 				=	"[1;33m"
blue 				=	"[1;34m"
magenta 			=	"[1;35m"
cyan 				=	"[1;36m"
white 				=	"[1;37m"

bg_black 			=	"[40m"
bg_red 				=	"[41m"
bg_green 			=	"[42m"
bg_yellow 			=	"[43m"
bg_blue 			=	"[44m"
bg_magenta 			=	"[45m"
bg_cyan 			=	"[46m"
bg_white 			=	"[47m"

reset 				=	"[0m"

#################################################################################
#                                                                               #
#                   ##                                             #####        #
#                   ##                                             #            #
#                   ##                                           #######        #
#                   ##                                              ##          #
#       #####       ##          ####           #    #    #          ##          #
#       #           ##         #    #          #    #    #          ##          #
#     ########      ########################### #### ####           ##          #
#                                                                               #
#################################################################################