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

void throw_error(char *msg)
{
  printf("Error: %s\n", msg);
}

int find_len(char *str, bool inside_quotes)
{
  int len;

  // len = ft_strchr(str + 1, '|', inside_quotes);
  len = ft_strchr(str + 1, ' ', inside_quotes);
  if(len != -1)
    return len;
  // len = ft_strchr(str + 1, ' ', inside_quotes);
  len = ft_strchr(str + 1, '|', inside_quotes);
  if(len != -1)
    return len;
  return ft_strlen(str);
}

void ft_lexer(char *command, t_shell *shell)
{
  int i;
  int db_quote;
  int s_quote;
  int w_space;
  char *buffer;

  i = 0;
  db_quote = 0;
  s_quote = 0;
  w_space = 0;
  buffer = NULL;
  
  while(command[i])
  {

    s_quote = 0;
    db_quote = 0;
    w_space = 0;
    // printf("--------------- %c ------------------\n", command[i - 1]);
    while (command[i] && ft_isspace(command[i]))
      i++;
    if(command[i] == '\'')
    {
      i++;
      s_quote = ft_strchr(command + i + 1, '\'', true);
      if(s_quote == -1)
      {
        throw_error("single quote must be closed");
        return;
      }
      buffer = ft_substr(command, i, s_quote);
      i += s_quote;
    }
    else if(command[i] == '\"')
    {
      // printf("command[i] == %c\n", command[i]);
      i++;
      // printf("---> %s\n", command + i);
      db_quote = ft_strchr(command + i + 1, '\"', true);
      if(db_quote == -1)
      {
        throw_error("double quote must be closed");
        return;
      }
      buffer = ft_substr(command, i, db_quote);
      i += db_quote;
    }
    else
    {
      w_space = find_len(command + i, false);
      // printf("===> %d\n", w_space);
      if(w_space == -1)
      {
        throw_error("space must be closed");
        return;
      }
      buffer = ft_substr(command, i, w_space);
      i += w_space;
    }
    printf("%s --- %zu\n", buffer, ft_strlen(buffer));
    // if(!ft_strcmp(buffer, "|"))
    //   printf("------> pipe was found\n");
    i++;
  }
}
