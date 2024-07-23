#include "minishell.h"

int ft_isspace(char c)
{
  if((c >= 9 && c <= 13) || c == 32)
    return 1;
  return 0;
}

void handle_signle_quote(t_shell *shell, int *s_quote)
{
  *s_quote += 1;
  // printf("---> single: %d\n", *s_quote);
  if(*s_quote == 2)
  {
    *s_quote = 0;
    shell->state = NORMAL;
  }
  else
    shell->state = S_QUOTE;
}

void handle_double_quote(t_shell *shell, int *db_quote)
{
  *db_quote += 1;
  // printf("---> double: %d\n", *db_quote);
  if(*db_quote == 2)
  {
    *db_quote = 0;
    shell->state = NORMAL;
  }
  else
  shell->state = D_QUOTE;
}

void get_cmd_type(char *cmd)
{
  t_type type;
  if(!cmd)
    return;
  printf("command ------------> %s\n", cmd);
  if(ft_isalpha(cmd[0]))
    printf("word\n");
  if(cmd[0] == '$')
    printf("variable\n");
  else if(cmd[0] == '-')
    printf("flag");
  else if(cmd[0] == ' ')
    printf("white space");
  else if(cmd[0] == '|')
    printf("pipe");
}

void catch_command(t_shell *shell, char *command, int i, int len)
{
  char *str;
  t_node *new_node;
  // int i;

  str = ft_substr(command, i - len, len);
  printf("str: %s\n", str);
  get_cmd_type(str);
  // new_node = ft_lstnew(str, shell->type,  );
}

void catch_pipe(char c)
{
  if(c == '|')
    printf("a pipe was found\n");
}

void ft_lexer(char *command, t_shell *shell)
{
  int i;
  int db_quote;
  int s_quote;
  int len;

  db_quote = 0;
  s_quote = 0;
  i = 0;
  while (command[i] && ft_isspace(command[i]))
    i++;
  while (command[i])
  {
    len = 0;
    if(command[i] == '\'')
    {
      handle_signle_quote(shell, &s_quote);
      i++;
    }
    else if(command[i] == '\"')
    {
      handle_double_quote(shell, &db_quote);
      i++;
    }
    while (command[i] && ft_isspace(command[i]))
      i++;
    while (command[i] && (!ft_isspace(command[i]) && command[i] != '\'' && command[i] != '\"') )
    {
      len++;
      i++;
      if(command[i - 1] == '|')
        break;
    }
    if(len > 0)
    {
      // printf("state --> %d\n", shell->state);
      catch_command(shell, command, i, len);
    }
    i++;
  }
}
