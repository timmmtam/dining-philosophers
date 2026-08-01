# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timtan <timtan@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/18 15:47:05 by timtan            #+#    #+#              #
#    Updated: 2026/04/18 17:17:59 by timtan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread -IHeaders

VPATH = srcs:srcs/utils

OBJDIR = objs

SRC_FILES = main.c	ft_atol.c

OBJ_FILES = $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	cc $(CFLAGS) -c $(<) -o $(@)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	cc $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fcllean re
