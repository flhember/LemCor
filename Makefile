# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flhember <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:41:02 by flhember          #+#    #+#              #
#    Updated: 2020/02/12 17:24:16 by flhember         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = clang
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wpadded

#-----------------------------------------SRC/INC-------------------------------#

LEM_IN=		main lem_in parsing_map init_struct ft_lst_stock creat_adja_lst	\
		   	ft_free parsing_main parsing_map_sec ft_stock_pipe ft_lstsize	\
		   	check_name verif_pos algo_main ft_bfs ft_other_road ft_best_road\
			ft_use_bfs ft_stock_road bfs_for_best ft_verif_block_road		\
		   	ft_print_res sort_road choose_road ft_use ft_stock_road_bis		\
			ft_free_bis ft_use_bfs_bis ant_rep choose_road_use nb_ant_road	\
			sort_road_use

INC = lem_in.h

#---------------------------------------PATH/FILES-------------------------------#

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
LIB_PATH = ./libft/
INC_PATH = ./includes/

LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))
LIB_HEADER = $(addprefix $(LIB_PATH), $(INC_PATH))

SRC_FILES= $(LEM_IN:%=%.c)
INC_FILES = $(addprefix $(INC_PATH), $(INC))
OBJ_FILES = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

#------------------------------------------RULES--------------------------------#

all: $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_FILES): $(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	$(CC) $(CFLAGS) -c -I $(INC_PATH) -I$(LIB_HEADER) $< -o $@
	echo "\033[40mCompilation of \033[1m$(notdir $<)\033[0m \033[32mdone.\033[0m"

$(LIB): FORCE
	$(MAKE) -C $(LIB_PATH)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB) -o $(NAME) -I $(INC_PATH) -I $(LIB_HEADER)
	echo "\033[1;32m$(notdir $(NAME))\033[1;0m\033[32m created.\033[0m"

FORCE:

clean:
	$(RM) -R $(OBJ_PATH)
	$(MAKE) clean -C $(LIB_PATH)
	echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIB_PATH)
	echo "\033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.SILENT:
.PHONY: clean, fclean, all, re, FORCE
