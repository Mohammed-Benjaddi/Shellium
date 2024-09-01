#include <minishell.h>

bool correct_path(char *path, char *cmd, bool is_path)
{
  if(is_path)
  {
    if(!ft_strcmp(path, cmd))
      return true;
    return false;
  }  
  return true;
}

int get_arr_len(char **arr)
{
  int i;

  i = 0;
  while(arr[i])
    i++;
  return i;
}

static size_t get_delimiters_len(char **args)
{
  size_t i;
  size_t len;

  i = 0;
  len = 0;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<")) // and [i+1] != '\0'
      len++;
    i++;
  }
  return len;
}

char **get_herdoc_delimiter(char **args, t_all *all)
{
  size_t i;
  size_t len;
  char **delimiters;

  i = 0;
  len = get_delimiters_len(args);
  if(!len)
    return NULL;
  delimiters = malloc(sizeof(char *) * (len + 1));
  i = 0;
  len = 0;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<"))
    {
      i++;
      if(!args[i + 1])
        return (throw_error("syntax error near unexpected token", all, 258), NULL);
      else
        delimiters[len++] = ft_strdup(args[i + 1]);
    }
    i++;
  }
  delimiters[len] = NULL;
  return delimiters;
}
