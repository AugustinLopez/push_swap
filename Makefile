# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/12 11:06:27 by aulopez           #+#    #+#              #
#    Updated: 2019/04/11 16:58:51 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=both
NAME_1=checker
NAME_2=push_swap
NAME_LIB=$(PATH_LIB)libft.a

# --- 1.Source/Header ----------------------------------------------------------

SRC_CHECKER=	ch_main \
				ch_parsing \
				ch_show_sorting
SRC_PUSHSWAP=	ps_main \
				ps_squash_instruction \
				quicksort_main \
					quicksort_little_a \
					quicksort_little_b \
					quicksort_utils \
				insertsort_main \
					insertsort_mode \
					insertsort_step1 \
					insertsort_step2 \
						insertsort_step2_nbr
SRC_BOTH=	operand_main \
				operand_p \
				operand_rr_r_s \
			init_stack \
			utils \
				utils_stack \
				utils_index \
			ft_quicksort
HDR=	libft.h \
		pushswap.h

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

all: $(NAME)

$(NAME): $(NAME_1) $(NAME_2)

$(NAME_1): $(NAME_LIB) $(OBJ_BOTH) $(OBJ_CHECKER) $(INCLUDES)
	-@printf "\r$(GREEN)Compiling $(NAME_2):$(EOC)         "
	@$(OPTION_C1) $@ $(OBJ_CHECKER) $(OBJ_BOTH) $(OPTION_C2)
	-@echo "$(GREEN)$(BOLD)Done.$(EOC)      \b\b\b\b\b\b"

$(NAME_2): $(NAME_LIB) $(OBJ_BOTH) $(OBJ_PUSHSWAP) $(INCLUDES)
	-@printf "\r$(GREEN)Compiling $(NAME_1):$(EOC)           "
	@$(OPTION_C1) $@ $(OBJ_PUSHSWAP) $(OBJ_BOTH) $(OPTION_C2)
	-@echo "$(GREEN)$(BOLD)Done.$(EOC)      \b\b\b\b\b\b"

$(NAME_LIB):
	-@echo "=== SUBPROCESS - Updating library ==="
	@make -C $(PATH_LIB)
	-@echo "======== SUBPROCESS - Over =========="

$(PATH_OBJ_B)%.o:$(PATH_SRC_B)%.c $(INCLUDES)
	-@printf "\r%50s" " "
	-@printf "\r$(CYAN)Creating %-35s$(EOC)" "$@$ "
	@$(OPTION_O) $< -o $@

$(PATH_OBJ_C)%.o:$(PATH_SRC_C)%.c $(INCLUDES)
	-@printf "\r%50s" " "
	-@printf "\r$(PURPLE)Creating $@$ $(EOC)"
	@$(OPTION_O) $< -o $@

$(PATH_OBJ_P)%.o:$(PATH_SRC_P)%.c $(INCLUDES)
	-@printf "\r%50s" " "
	-@printf "\r$(BLUE)Creating $@$ $(EOC)"
	@$(OPTION_O) $< -o $@

clean:
	-@printf "$(RED)Deleting project objects:$(EOC)    "
	@rm -f $(OBJ_CHECKER) $(OBJ_PUSHSWAP) $(OBJ_BOTH)
	@make -sC $(PATH_LIB) clean >> /dev/null
	-@echo "$(GREEN)$(BOLD)Done.$(EOC)"

fclean: clean
	-@printf "$(RED)Removing executables:$(EOC)        "
	@rm -f $(NAME_1) $(NAME_2)
	@make -sC $(PATH_LIB) fclean > /dev/null
	-@echo "$(GREEN)$(BOLD)Done.$(EOC)"

re: fclean all

.PHONY: both all clean fclean re
