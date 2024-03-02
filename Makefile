NAME		= ft_ping

INCLUDES	= -I ./includes/ -I ./libft/

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES) -g
LIBS		= -L libft/ -lft -lm

SRCS		=	main.c		\
				utils.c		\
				socket.c

OBJS		= $(addprefix ./src/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re