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

bool valid_filename(char **args, char *filename)
{
  int i;

  i = 0;
  if(!ft_strcmp(filename, "export"))
    printf("%s%s%s\n", RED, args[0], NC);
  else
    printf("%s%s%s\n", CYAN, args[0], NC);
  return true;
}

char *get_output_redirection_file(char **args, t_all *all)
{
  int i;
  int fd;
  char *out_file;

  i = 0;
  out_file = NULL;
  while(args[i])
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
        out_file = ft_strdup(args[i + 1]);
        if(!valid_filename(args, out_file))
          throw_error("ambiguous redirect", all, 1);
        fd = open(out_file, O_CREAT | O_RDWR, 0777);
        close(fd);
      }
    }
    i++;
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



