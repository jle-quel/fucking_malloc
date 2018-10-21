# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: _root <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/24 09:48:45 by _root             #+#    #+#              #
#    Updated: 2018/09/25 05:23:57 by jle-quel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc
LINK_NAME = libft_malloc.so

SRC_NAME =	free.c				\
			malloc.c			\
			realloc.c			\
			utils.c				\
			new_page.c			\
			search_page.c		\
			calloc.c			\
			show_alloc_mem.c	\
			lib.c				\
			realloc.c			\

OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = 

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -shared -o $@ $(LDFLAGS) $(LDLIBS)
	@ln -sF $(NAME) $(LINK_NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH)
	@echo "$(GREEN)[✓]$(NC) Source compiled : $<"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[-]$(NC) Objects cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC) Program clear"
	@rm -rf $(LINK_NAME)
	@echo "$(RED)[-]$(NC) Link clear"

re:fclean
	@make
