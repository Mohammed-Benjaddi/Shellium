#include "minishell.h"

char *get_input_redirection_file(char **args)
{
  int i;
  char *in_file;

  i = 0;
  in_file = NULL;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && ft_strcmp(args[i + 1], "<") && ft_strcmp(args[i - 1], "<"))
    {
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
      {
        printf("======> %s ---- %s\n", args[i], args[i + 1]);
        free(in_file);
        in_file = ft_strdup(args[i + 1]);
      }
    }
    i++;
  }
  return in_file;
}

char *get_output_redirection_file(char **args)
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
        throw_error("syntax error near unexpected token `newline'");
      else
      {
        if(!ft_strcmp(args[i + 1], ">"))
          return NULL;
        free(out_file);
        out_file = ft_strdup(args[i + 1]);
        fd = open(out_file, O_CREAT | O_RDWR, 0777);
        close(fd);
      }
    }
    i++;
  }
  return out_file;
}

char *get_append_to_file(char **args)
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
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
      {
        free(file);
        file = ft_strdup(args[i + 1]);
        fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
        // protect file!
        close(fd);
      }
    }
    i++;
  }
  return file;
}

char **get_herdoc_delimiter(char **args)
{
  size_t i;
  size_t len;
  char **delimiters;

  i = 0;
  len = 0;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<")) // and [i+1] != '\0'
      len++;
    i++;
  }
  delimiters = malloc(sizeof(char *) * len + 1);
  i = 0;
  len = 0;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<")) // and [i+1] != '\0'
    {
      i++;
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
        delimiters[len++] = ft_strdup(args[i + 1]);
    }
    i++;
  }
  return delimiters;
}
