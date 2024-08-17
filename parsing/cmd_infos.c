#include "minishell.h"

char  *get_path(char *cmd)
{
  int i;
  char *path;
  char *command;
  char **all_paths;
  
  i = 0;
  path = ft_strdup(getenv("PATH"));
  all_paths = ft_split(path, ':');
  if(!all_paths)
    return NULL;
  free(path);
  path = NULL;
  // all_paths = NULL;
  while (all_paths[i])
  {
    command = ft_strjoin(all_paths[i], "/");
    path = ft_strjoin(command, cmd);
    free(command);
    command = NULL;
    if(access(path, X_OK) == 0)
    {
      ft_free(all_paths);
      // free(command);
      return path;
    }
    free(path);
    path = NULL;
    i++;
  }
  ft_free(all_paths);
  return NULL;
}

char *get_input_redirection_file(char **args)
{
  int i;
  char *in_file;

  i = 0;
  in_file = NULL;
  while(args[i])
  {
    if(!ft_strcmp(args[i], "<"))
    {
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
      {
        free(in_file);
        in_file = ft_strdup(args[i + 1]);
      }
    }
    // else if(!ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], ">"))
    // {
    //   if(!args[i - 1])
    //     throw_error("syntax error near unexpected token `newline'");
    //   else if (i == 1)
    //     return NULL;
    //   else
    //   {
    //     free(in_file);
    //     in_file = ft_strdup(args[i - 1]);
    //     return in_file;
    //   }
    // }
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
        //must create a file
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
    // printf("args[i] --> %s\n", args[i]);
    if(!ft_strcmp(args[i], ">") && !ft_strcmp(args[i + 1], ">")) // and [i+1] != '\0'
    {
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
       {
        free(file);
        file = ft_strdup(args[i + 1]);
        // must create a file
        fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
        // protect file!
        close(fd);
        // fd = open(file, O_CREAT | O_RDWR);
        // close(fd);
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