#include "minishell.h"



void change_dir(char *cmd)
{
  char cwd[100];
  chdir("/home/simo");
  getcwd(cwd, 100);
  printf("---> %s\n", cwd);
}


char *ft_strncpy(char *str, int size)
{
  int i;
  char *result;

  i = 0;
  result = malloc(sizeof(char) * size + 1);
  while (i < size)
  {
    result[i] = str[i];
    i++;
  }
  result[i] = '\0';
  return result;
}

char *get_cmd(char *read)
{
  printf("-- read from get cmd: %s\n", read);
  int i;
  char *cmd;

  i = 0;
  while (read[i] && read[i] != ' ')
    i++;
  cmd = ft_strncpy(read, i - 1);  

  return NULL;
}

int main()
{
  char *read = readline("minishell > ");
  if(!read)
  {
    printf("read is null\n");
    return 1;
  }

  get_cmd(read);

  // printf("cmd: %s\n", read);

  change_dir(read);

  free(read);

  return 0;
}
