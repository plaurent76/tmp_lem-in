# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plaurent <plaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 15:01:58 by eviana            #+#    #+#              #
#    Updated: 2019/08/22 16:26:54 by plaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= lem-in
SRC_PATH	= srcs/
OBJ_PATH	= objs/
LIB			= libft/libft.a
FLAGS		= -Wall -Werror -Wextra 
CC			= gcc $(FLAGS)
SRC_SUFFIX	= .c
COMMON =	main \
			get_lines \
			error \
			memory \
			array \
			matrix \
			ants \
			links \
			rooms \
			path \
			count \
			env_utils \
			str_utils \
			basics \
			parser \
			parser_utils \
			move_colony \
			print_anthill \
			combo \
			prepare_env	\
			ek	\
			bfs

SRC_FILES = $(addsuffix $(SRC_SUFFIX),$(COMMON))
OBJ_FILES = $(SRC_FILES:.c=.o)
SRC		= $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJ		= $(addprefix $(OBJ_PATH),$(OBJ_FILES))

#color
YELLOW		= "\\033[33m"
BLUE		= "\\033[34m"
RED			= "\\033[31m"
WHITE		= "\\033[0m"
CYAN		= "\\033[36m"
GREEN		= "\\033[32m"
BOLD		= "\\033[1m"
PINK		= "\\033[95m"

#command
EOLCLR		= "\\033[0K"
#unicode
CHECK		= "\\xE2\\x9C\\x94"
OK			= " $(CYAN)$(CHECK)$(WHITE)"

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@printf "\r$(EOLCLR)[$(NAME)] >>>>>>>>>>>>>>\t$(YELLOW)$(BOLD)"\
	"lem_in compiled\t\t"$(OK)'\n'
	@ $(CC) -I./includes $(OBJ) $(LIB) -o $@
	@printf "\r$(EOLCLR)[$(NAME)] >>>>>>>>>>>>>>\t$(GREEN)$(BOLD)"\
	"build successful\t"$(OK)'\n'

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) : 
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "\r$(EOLCLR)[$(NAME)] compiling\t$(BOLD)$(YELLOW)$<$(WHITE)"
	@$(CC) -I./includes -o $@ -c $<
	@printf '\t'$(OK)

clean :
	@make clean -C libft
	@printf "[$(NAME)] removing\t$(PINK)all obj file$(WHITE)"
	@rm -rf $(OBJ_PATH)
	@printf '\t\t'$(OK)'\n'

fclean : clean
	@make fclean -C libft
	@printf "[$(NAME)] erasing\t$(PINK)$(NAME)$(WHITE)"
	@rm -f $(NAME)
	@rm -rf lem-in.dSYM
	@printf '\t\t\t'$(OK)'\n'

re : fclean all

norm :
	@norminette srcs/ include/

.PHONY: all clean fclean re norm
