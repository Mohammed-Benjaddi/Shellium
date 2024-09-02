#include <minishell.h>

void throw_error(char *msg, t_all *all, int nbr)
{
  int i;

  i = 0;
  write(2, "Error: ", 7);
  while(msg[i])
    write(2, &msg[i++], 1);
  write(2, "\n", 1);
  all->exit_status = nbr;
  all->error = true;
}

int find_pipe_index(char *str)
{
  int i;
  int len;

  i = 0;
  len = ft_strlen(str);
  while (i < len && str[i])
  {
    if(str[i] == PIPE)
      return i;
    else if(i < len && str[i] == DOUBLE_QUOTE)
    {
      i++;
      while(i < len && str[i] && str[i] != DOUBLE_QUOTE)
        i++;
    }
    else if(i < len && str[i] == SINGLE_QUOTE)
    {
      i++;
      while(i < len && str[i] && str[i] != SINGLE_QUOTE)
        i++;
    }
    i++;
  }
  return -1;
}

int args_counter(char *str, int len)
{
  int i;
  int s_quote;
  int d_quote;
  int words;

  i = 0;
  s_quote = 0;
  d_quote = 0;
  words = 0;
  if(len == -1)
    len = ft_strlen(str);
  while(str[i] && i < len)
  {
    while (str[i] && str[i] == SPACE && i < len)
      i++;
    if (str[i] && str[i] != SPACE && s_quote == 0 && d_quote == 0 && i < len)
      words++;
    while (str[i] && str[i] != SPACE && i < len)
    {
      if (str[i] == SINGLE_QUOTE)
        s_quote++;
      else if (str[i] == DOUBLE_QUOTE)
        d_quote++;
      if (s_quote == 2)
        s_quote = 0;
      if (d_quote == 2)
        d_quote = 0;
      i++;
    }
  }
  return words;
}

void ft_free(char **args, int len)
{
  int i;

  i = 0;
  if(!args)
    return;
  while(i < len)
  {
    if(args[i] != NULL)
      free(args[i]);
    i++;
  }
  free(args);
  args = NULL;
}

int nums_of_chars(char *str, char c)
{
  int i;
  int counter;

  i = 0;
  counter = 0;
  if(!str)
    return counter;
  while(str[i])
  {
    if(str[i] == c)
      counter++;
    i++;
  }
  return counter;
}
