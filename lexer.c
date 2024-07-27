#include "minishell.h"

int ft_isspace(char c)
{
  if((c >= 9 && c <= 13) || c == 32)
    return 1;
  return 0;
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

void ft_lexer(char *command, t_cmd **head)
{
  int i;
  int j;
  int len;
  char *buffer;
  int pipe_idx;
  int words;
  char **args;
  t_cmd *cmd;

  i = 0;
  j = 0;
  buffer = NULL;
  while(command[i])
  {
    j = 0;
    pipe_idx = find_pipe_index(command + i);
    if(pipe_idx == -1)
      pipe_idx = ft_strlen(command);
    words = words_counter(command + i, pipe_idx);
    args = malloc(sizeof(char *) * words + 1);
    if(!args)
      return;
    printf("%swords ---- %d%s\n", GREEN, words, NC);
    while(i < pipe_idx)
    {
      len = 0;
      while (command[i] && ft_isspace(command[i]))
        i++;
      if(command[i] == '\'')
      {
        i++;
        len = ft_strchr(command + i + 1, '\'', true);
        if(len == -1)
        {
          throw_error("single quote must be closed");
          return;
        }
        buffer = ft_substr(command, i, len);
        i += len;
      }
      else if(command[i] == '\"')
      {
        i++;
        // len = ft_strchr(command + i + 1, '\"', true);
        len = ft_strchr(command + i, '\"', true);
        if(len == -1)
        {
          throw_error("double quote must be closed");
          return;
        }
        // buffer = ft_substr(command, i, len);
        buffer = ft_substr(command + i, 0, len);
        i += len;
      }
      else
      {
        len = find_len(command + i, false);
        if(len == -1)
        {
          throw_error("space must be closed");
          return;
        }
        buffer = ft_substr(command, i, len);
        i += len;
      }
      args[j] = buffer;
      printf("buffer: %s\n", buffer);
      j++;
      i++;
    }
    args[j] = NULL;
    cmd = ft_lstnew(args, words);
    ft_lstadd_back(head, cmd);
    ft_free(args);
    i++;
  }
}
