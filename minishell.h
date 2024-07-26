#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

// typedef enum e_type 
// { 
//   WORD = 'a',
//   WHITE_SPACE = ' ',
//   PIPE = '|',
//   ENV_VAR = '$',
//   DO_QUOTE = '\"',
//   SI_QUOTE = '\'',
//   SEMICOLON = ';',
//   RED_IN = '<',
//   RED_OUT = '>',
//   FLAG = '-',
//   // RED_APPEND = '>',
//   BACKSLASH = '\\',
//   NONE = '0',
// } t_type;

typedef enum e_state
{
  D_QUOTE,
  S_QUOTE,
  NORMAL,
} t_state;

typedef struct s_command_line {
char *cmd; // The command name (e.g., "echo", "ls")
char *full_path; // The full path to the command (e.g., "/bin/echo", "/bin
char *args; // Array of arguments including the command
int  arg_count; // Number of arguments
char *in_file; // For input redirection (<)
char *out_file; // For output redirection (>)
char *append_file; // For append redirection (>>)
char *heredoc_delimiter; // For heredoc (<<)
char *heredoc_content; // Content of heredoc
int   pipe; // 1 if this command pipes to next, 0 otherwise
struct s_command_line *next; // Pointer to next command in pipeline
} t_cmd;

typedef struct s_shell
{
  t_cmd *head;
  int     size;
  t_state state;
  int nums_of_pipes;
} t_shell;

// libc functions
char *ft_strdup(char *str);
char	*ft_strjoin(char   *s1, char   *s2);
size_t ft_strlen(char *str);
char	*ft_substr(char   *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst,   char *src, size_t dstsize);
char    **ft_split(char   *s, char c);
int ft_strcmp(char *s1, char *s2);
int ft_isalpha(char c);

// ft_list.c
t_cmd	*ft_lstnew(char *content);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);

void ft_init(t_shell *shell);


// ft_lexer.c
void ft_lexer(char *command, t_shell *shell);

#endif