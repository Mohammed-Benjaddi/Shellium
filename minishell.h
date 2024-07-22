#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum e_type 
{ 
  WORD = 'a',
  WHITE_SPACE = ' ',
  PIPE = '|',
  ENV_VAR = '$',
  DO_QUOTE = '\"',
  SI_QUOTE = '\'',
  SEMICOLON = ';',
  RED_IN = '<',
  RED_OUT = '>',
  // RED_APPEND = '>',
  BACKSLASH = '\\',
} t_type;

typedef enum e_state
{
  D_QUOTE,
  S_QUOTE,
  NORMAL,
} t_state;

typedef struct s_node
{
  char *content;
  int length;
  t_type type;
  t_state state;
  struct s_node *next;
  struct s_node *prev;
}             t_node;

typedef struct s_shell
{
  t_node *head;
  t_node *rear;
  int     size;
  t_state state;
} t_shell;

// libc functions
char *ft_strdup(char *str);
char	*ft_strjoin(char   *s1, char   *s2);
size_t ft_strlen(char *str);
char	*ft_substr(char   *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst,   char *src, size_t dstsize);
char    **ft_split(char   *s, char c);
int ft_strcmp(char *s1, char *s2);

// ft_list.c
t_node *ft_lstnew(char *content, t_type type, t_state state);
void ft_lstadd_back(t_shell **shell, t_node *new_node);
void ft_init(t_shell *shell);


// ft_lexer.c
void ft_lexer(char *command, t_shell *shell);

#endif