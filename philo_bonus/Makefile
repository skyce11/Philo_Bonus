RED		= '\033[31m'
GREEN	= '\033[1;32m'
YELLOW	= '\033[33m'
BLUE	= '\033[34m'
PURPLE	= '\033[1;35m'
CIAN	= '\033[36m'
WHITE	= '\033[37m'
NONE	= '\033[0m'

SRCS = 	./src/ft_args.c \
	./src/ft_atoi.c 	\
	./src/ft_error.c 	\
	./src/ft_kill.c 	\
	./src/ft_routine.c  \
	./src/init_all.c 	\
	./src/open_sem.c 	\
	./src/philo_utils.c \
	./src/printer.c 	\
	./src/main.c

 
OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

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
