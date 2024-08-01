CC = cc
CFLAGS = #-Wall -Wextra -Werror

NAME = minishell

SRCS = main.c ft_libc1.c ft_split.c ft_list.c lexer.c utils_1.c utils_2.c
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
