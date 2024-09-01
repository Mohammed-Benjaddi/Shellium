#include "minishell.h"

char *get_input_redirection_file(char **args, t_all *all)
{
  int i;
  char *in_file;

  i = 0;
  in_file = NULL;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && ft_strcmp(args[i + 1], "<"))
    {
      if(i == 0 || (i > 0 && ft_strcmp(args[i - 1], "<")))
      {
        if(!args[i + 1])
          return (throw_error("syntax error near unexpected token", all, 258), NULL);
        else
        {
          free(in_file);
          in_file = ft_strdup(args[i + 1]);
        }
      }
    }
    i++;
  }
  return in_file;
}

// bool is_valid_filename(char **args, char *filename)
// {
//   int i;

//   i = 0;
//   // printf("%s%s%s\n", CYAN, args[0], NC);
//   if(!fix_file_name(filename) && args[0] && !ft_strcmp(args[0]))
//     return false;
//   return true;
// }


// void is_herdoc_delemiter(char **args, int i)
// {
//   if(i > 2)
//   {
//     if(ft_strcmp(args[i], "<"))
//   }
// }

char *check_filename(char **args, int i, t_all *all)
{
  char *buffer;
  char *result;
  char **words;
  int index;

  if(get_vars_length(args[i + 1]) > 0)
  {
    buffer = handle_variables(args[i + 1], all->env, get_vars_length(args[i + 1]), all);
    words = ft_split(buffer, ' ');
    if(!words)
      return free(buffer), throw_error("ambiguous redirect", all, 1), NULL;
    int i = 0;
    while (words[i])
      i++;
    if(i > 1)
      return ft_free(words, get_arr_len(words)), free(buffer), throw_error("ambiguous redirect", all, 1), NULL;
    else
      return buffer;
  }
  index = ft_strchr_pro(args[i + 1], DOUBLE_QUOTE, SINGLE_QUOTE, false); 
  if(index != -1 && args[i + 1][index - 1] == SINGLE_QUOTE)
    return find_and_remove(ft_strdup(args[i + 1]), SINGLE_QUOTE);    
  else if (index != -1 && args[i + 1][index - 1] == DOUBLE_QUOTE)
    return find_and_remove(ft_strdup(args[i + 1]), DOUBLE_QUOTE);
  return ft_strdup(args[i + 1]);
}

char *get_output_redirection_file(char **args, t_all *all)
{
  int i;
  int fd;
  char *out_file;

  i = -1;
  out_file = NULL;
  while(args[++i])
  {
    if(!ft_strcmp(args[i], ">"))
    {
      if(!args[i + 1])
        return (throw_error("syntax error near unexpected token", all, 258), NULL);
      else
      {
        if(!ft_strcmp(args[i + 1], ">"))
          return NULL;
        free(out_file);
        out_file = NULL;
        out_file = check_filename(args, i, all);
        fd = open(out_file, O_CREAT | O_RDWR, 0777);
        close(fd);
      }
    }
  }
  return out_file;
}

char *get_append_to_file(char **args, t_all *all)
{
  int i;
  int fd;
  char *file;

  i = 0;
  file = NULL;
  while(args[i])
  {
    if(!ft_strcmp(args[i], ">") && args[i + 1] && !ft_strcmp(args[i + 1], ">"))
    {
      i++;
      if(!args[i + 1])
        return (throw_error("syntax error near unexpected token", all, 258), NULL);
      else
      {
        free(file);
        file = ft_strdup(args[i + 1]);
        fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
        close(fd);
      }
    }
    i++;
  }
  return file;
}



