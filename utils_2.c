#include "minishell.h"

char  *get_path(char *cmd)
{
  int i;
  char *path;
  char **all_paths;
  
  i = 0;
  path = ft_strdup(getenv("PATH"));
  all_paths = ft_split(path, ':');

  while(all_paths[i])
  {
    printf("path --> %s\n", all_paths[i]);
    if(access(all_paths[i], X_OK))
      printf("---> yes\n");
    else
      printf("---> no\n");
    i++;
  }
  return ft_strdup(cmd);
}

// char *handle_redirections(t_cmd *cmd)
// {
//   int i;

//   i = 0;
//   while()
//   {

//   }
// }
