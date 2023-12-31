# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migonzal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 10:42:54 by migonzal          #+#    #+#              #
#    Updated: 2022/07/19 11:24:16 by migonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### ------ COLORS ------ ###


RED		= '\033[31m'
GREEN	= '\033[1;32m'
YELLOW	= '\033[33m'
BLUE	= '\033[34m'
PURPLE	= '\033[1;35m'
CIAN	= '\033[36m'
WHITE	= '\033[37m'
NONE	= '\033[0m'

SRCS = 	args.c \
		ft_check.c \
		ft_lists.c \
		philos_func.c \
		threads_func.c \
		magic.c \
		main.c \
		atoi.c


OBJS = $(SRCS:.c=.o)

NAME = philo

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra #-g3 -fsanitize=thread


RM = rm -f

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(ASAN_FLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -g3 -fsanitize=thread
	@echo $(GREEN) $(NAME)": All ready to work"

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo $(RED) "Files deleted"

re: fclean $(NAME)

.PHONY: all clean fclean re
