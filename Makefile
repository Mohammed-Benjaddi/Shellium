CC = cc
CFLAGS = #-Wall -Wextra -Werror

HEADER = -I ./include/

NAME = minishell

SRCS = ./parsing/main.c ./parsing/ft_libc1.c ./parsing/ft_split.c \
 			./parsing/ft_list.c ./parsing/lexer.c ./parsing/utils_1.c ./parsing/cmd_infos.c
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(HEADER) $(OBJS) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
