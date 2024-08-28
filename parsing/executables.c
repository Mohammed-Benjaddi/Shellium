#include <minishell.h>

size_t get_slash_index(char *cmd)
{
  size_t i;
  size_t index;

  i = 0;
  index = -1;
  if(!cmd)
    return -1;
  while(cmd[i])
  {
    if(cmd[i] == SLASH)
      index = i;
    i++;
  }
  return index;
}

char *get_executable(char *cmd)
{
  size_t i;
  char **arr;
  char *filename;
  char *path;
  size_t slash_index;
  char cwd[256];

  i = 0;
  // printf("---> %s\n", cmd);
  slash_index = 0;
  if(get_slash_index(cmd) == -1)
  {
    // printf("slash not found\n");
    return NULL;
  }
  arr = ft_split(cmd, SLASH);
  if(!arr)
    return NULL;
  while(arr[i + 1] != NULL)
    i++;
  filename = ft_strdup(arr[i]);
  // printf("path name ---> %s\n", filename);
  ft_free(arr, get_arr_len(arr));
  if(!filename)
    return NULL;
  slash_index = get_slash_index(cmd);
  path = ft_strndup(cmd, slash_index + 1);
  chdir(path);
  free(path);
  getcwd(cwd, sizeof(cwd));
  path = ft_strjoin(ft_strjoin(ft_strdup(cwd), "/"), filename);
  free(filename);
  if(path != NULL)
    return path;
  return NULL;
}
