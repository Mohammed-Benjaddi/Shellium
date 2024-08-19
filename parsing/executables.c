#include <minishell.h>

size_t get_slash_index(char *cmd)
{
  size_t i;
  size_t index;

  i = 0;
  index = -1;
  while(cmd[i])
  {
    if(cmd[i] == SLASH)
      index = i;
    i++;
  }
  return index;
}

void get_executable(char *cmd)
{
  size_t i;
  char **arr;
  char *filename;
  char *path;
  size_t slash_index;
  char cwd[256];

  i = 0;
  slash_index = 0;
  if(get_slash_index(cmd) == -1)
    return;
  arr = ft_split(cmd, SLASH);
  if(!arr)
  {
    printf("----> no slash here\n");
    return;
  }
  while(arr[i + 1] != NULL)
  {
    printf("%s--> %s%s\n", MAGENTA, arr[i + 1], NC);
    i++;
  }
  filename = ft_strdup(arr[i]);
  if(!filename)
    return;
  slash_index = get_slash_index(cmd);
  path = ft_strndup(cmd, slash_index + 1);
  chdir(path);
  getcwd(cwd, sizeof(cwd));  
  printf("filename: %s\npath is: %s\n", filename, cwd);
  // return filename;
  // printf("file name: %s\n", filename);
}
