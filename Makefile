# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/12 11:06:27 by aulopez           #+#    #+#              #
#    Updated: 2019/03/19 16:22:05 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1=checker
NAME_2=push_swap

# --- 1.Source/Header ----------------------------------------------------------

SRC_CHECKER=ch_main
SRC_PUSHSWAP=ps_main ps_pivot ps_sort ps_sort_only_a ps_sort_only_b ps_instruction ps_backtrack
SRC_BOTH=operand_main operand_p operand_rr_r_s handle_stack utils
HDR=libft.h pushswap.h

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=includes/
PATH_SRC_C=srcs/_checker/
PATH_OBJ_C=srcs/obj/
PATH_SRC_B=srcs/
PATH_OBJ_B=srcs/obj/
PATH_SRC_P=srcs/_push_swap/
PATH_OBJ_P=srcs/obj/
PATH_LIB=libft/

# --- 3.File Variables ---------------------------------------------------------

OBJ_CHECKER=$(SRC_CHECKER:%=$(PATH_OBJ_C)%.o)
OBJ_PUSHSWAP=$(SRC_PUSHSWAP:%=$(PATH_OBJ_P)%.o)
OBJ_BOTH=$(SRC_BOTH:%=$(PATH_OBJ_B)%.o)
INCLUDES=$(HDR:%=$(PATH_HDR)%)

# --- 4.Compilation Variables --------------------------------------------------

CC=gcc
FLAGS=-Wall -Wextra -Werror -g3
OPTION_O=$(CC) $(FLAGS) -c -I$(PATH_HDR)
OPTION_C1=$(CC) $(FLAGS) -o
OPTION_C2=-I$(PATH_HDR) -L$(PATH_LIB) -lft
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m
BOLD=\033[1m
ITALIC=\033[3m
UNDERLINE=\033[4m
STRIKETHROUGH=\033[9m
EOC=\033[0m

# --- 5.Rules ------------------------------------------------------------------

all: $(NAME_1) $(NAME_2)

$(NAME_1): $(OBJ_BOTH) $(OBJ_CHECKER)
	@printf "\r$(YELLOW)Checking library:$(EOC)            "
	@make -C $(PATH_LIB) >> /dev/null
	@printf "$(GREEN)$(BOLD)Done.$(EOC)\n"
	@printf "$(YELLOW)Compiling $(NAME_1):$(EOC)           "
	@$(OPTION_C1) $@ $(OBJ_CHECKER) $(OBJ_BOTH) $(OPTION_C2)
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

$(NAME_2): $(OBJ_BOTH) $(OBJ_PUSHSWAP)
	@printf "\r$(YELLOW)Checking library:$(EOC)            "
	@make -C $(PATH_LIB) >> /dev/null
	@printf "$(GREEN)$(BOLD)Done.$(EOC)\n"
	@printf "$(YELLOW)Compiling $(NAME_2):$(EOC)         "
	@$(OPTION_C1) $@ $(OBJ_PUSHSWAP) $(OBJ_BOTH) $(OPTION_C2)
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

$(PATH_OBJ_B)%.o:$(PATH_SRC_B)%.c $(INCLUDES)
	@printf "\r$(CYAN)Creating %-25s$(EOC)" "$@$ "
	@$(OPTION_O) $< -o $@

$(PATH_OBJ_C)%.o:$(PATH_SRC_C)%.c $(INCLUDES)
	@printf "\r$(PURPLE)Creating %-25s$(EOC)" "$@$ "
	@$(OPTION_O) $< -o $@

$(PATH_OBJ_P)%.o:$(PATH_SRC_P)%.c $(INCLUDES)
	@printf "\r$(BLUE)Creating %-25s$(EOC)" "$@$ "
	@$(OPTION_O) $< -o $@

onlylib:
	@echo "$(YELLOW)Updating library:$(EOC)              "
	@make -C $(PATH_LIB) >> /dev/null
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

fcleanlib:
	@printf "$(YELLOW)Removing library: $(EOC)           "
	@make -C $(PATH_LIB) fclean > /dev/null
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

cleanlib:
	@printf "$(YELLOW)Deleting library objects:$(EOC)    "
	@make -C $(PATH_LIB) clean > /dev/null
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

clean: cleanlib
	@printf "$(YELLOW)Deleting project objects:$(EOC)    "
	@rm -f $(OBJ_CHECKER) $(OBJ_PUSHSWAP) $(OBJ_BOTH)
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

fclean: clean fcleanlib
	@printf "$(YELLOW)Deleting executables:$(EOC)        "
	@rm -f $(NAME_1) $(NAME_2)
	@echo "$(GREEN)$(BOLD)Done.$(EOC)"

re: fclean all

.PHONY: all clean fclean re fcleanlib cleanlib onlylib
