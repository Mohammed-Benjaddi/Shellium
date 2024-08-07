#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>

#define SINGLE_QUOTE '\''
#define DOUBLE_QUOTE '\"'
#define PIPE '|'
#define SPACE ' '
#define IN_RED '<'
#define OUT_RED '>'

# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define GREEN "\x1b[32m"
# define CYAN "\x1b[36m"
# define RED "\x1b[31m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define WHITE "\x1b[37m"

typedef struct s_command_line {
  char *cmd; // The command name (e.g., "echo", "ls")
  char *full_path; // The full path to the command (e.g., "/bin/echo", "/bin
  char **args; // Array of arguments including the command
  int  arg_count; // Number of arguments
  char *in_file; // For input redirection (<)
  char *out_file; // For output redirection (>)
  char *append_file; // For append redirection (>>)
  // char *append_from_file; // For append redirection (>>)
  char *heredoc_delimiter; // For heredoc (<<)
  char *heredoc_content; // Content of heredoc
  int   pipe; // 1 if this command pipes to next, 0 otherwise
  struct s_command_line *next; // Pointer to next command in pipeline
} t_cmd;

// typedef struct s_shell
// {
//   t_cmd *head;
//   int     size;
//   t_state state;
//   int nums_of_pipes;
// } t_shell;

typedef struct s_lexer
{
  int i;
  int j;
  char *buffer;
  int pipe_idx;
  int words;
  char **args;
  size_t length;
  int pipe;
} t_lexer;

// libc functions
char *ft_strdup(char *str);
char	*ft_strjoin(char   *s1, char   *s2);
size_t ft_strlen(char *str);
char	*ft_substr(char   *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst,   char *src, size_t dstsize);
char    **ft_split(char   *s, char c);
int ft_strcmp(char *s1, char *s2);
int ft_isalpha(char c);
int ft_strchr(char *str, char c);
int ft_strchr_pro(char *str, char c1, char c2, bool inside_quotes);
int ft_isspace(char c);

// ft_list.c
t_cmd	*ft_lstnew(char **args, int args_nbr, int pipe);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
// void  ft_init(t_shell *shell);
void    ft_lstclear(t_cmd **lst);

// ft_lexer.c
void ft_lexer(char *command, t_cmd **head);
bool is_symbol(char c);

// utils_1.c
void throw_error(char *msg);
int find_pipe_index(char *str);
size_t args_counter(char *str, int len);
void ft_free(char **args);
void print_list(t_cmd *head);
char *find_and_remove(char *str, char c);
void skip_reds(char *str, int *i, char c);

// cmd_infos.c
char *get_path(char *cmd);
char *get_input_redirection_file(char **args);
char *get_output_redirection_file(char **args);
// char *get_append_from_file(char **args);
char *get_append_to_file(char **args);

#endif
