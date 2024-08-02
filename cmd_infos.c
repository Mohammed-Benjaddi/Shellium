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
  free(path);
  path = NULL;
  while (all_paths[i])
  {
    command = ft_strjoin(all_paths[i], "/");
    path = ft_strjoin(command, cmd);
    free(command);
    if(access(path, X_OK) == 0)
    {
      // printf("%spath: %s%s\n", GREEN, path, NC);
      // ft_free(all_paths);
      // free(command);
      return path;
    }
    // free(command);
    free(path);
    // ft_free(all_paths);
    i++;
  }
  return NULL;
}

// char *handle_redirections(t_cmd *cmd)
// {
//   int i;

//   i = 0;
//   while()
//   {

//   }
// }

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
        free(out_file);
        out_file = ft_strdup(args[i + 1]);
        fd = open(out_file, O_CREAT | O_WRONLY);
        close(fd);
      } 
    }
    i++;
  }
  return out_file;
}

char *get_append_from_file(char **args)
{
  int i;

  i = 0;
  while(args[i])
  {
    if(!ft_strcmp(args[i], ">>"))
    {
      if(!args[i - 1])
        throw_error("syntax error near unexpected token `newline'");
      else
        return ft_strdup(args[i - 1]);
    }
    i++;
  }
  return NULL;
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
    if(!ft_strcmp(args[i], ">>"))
    {
      if(!args[i + 1])
        throw_error("syntax error near unexpected token `newline'");
      else
      {
        free(file);
        file = ft_strdup(args[i + 1]);
        fd = open(file, O_CREAT | O_WRONLY);
        close(fd);
      }
    }
    i++;
  }
  return file;
}
