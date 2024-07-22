#include "minishell.h"

int ft_isspace(char c)
{
  if((c >= 9 && c <= 13) && c == 32)
    return 1;
  return 0;
}

void handle_signle_quote(t_shell *shell, int *s_quote)
{
  *s_quote += 1;
  printf("---> single: %d\n", *s_quote);
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
  printf("---> double: %d\n", *db_quote);
  if(*db_quote == 2)
  {
    *db_quote = 0;
    shell->state = NORMAL;
  }
  else
  shell->state = D_QUOTE;
}

void ft_lexer(char *command, t_shell *shell)
{
  int i;
  int db_quote;
  int s_quote;

  db_quote = 0;
  s_quote = 0;
  i = 0;
  while (command[i] && ft_isspace(command[i]))
    i++;
  while (command[i])
  {
    if(command[i] == '\'')
      handle_signle_quote(shell, &s_quote);
    else if(command[i] == '\"')
      handle_double_quote(shell, &db_quote);
    i++;
  }
}
