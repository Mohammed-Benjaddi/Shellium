#include "minishell.h"



void change_dir(char *cmd)
{
  char cwd[100];
  chdir("/Documents");
  getcwd(cwd, 100);
  printf("---> %s\n", cwd);
}

int main()
{
  char *read = readline("minishell > ");
  if(!read)
  {
    printf("read is null\n");
    return 1;
  }

  printf("cmd: %s\n", read);

  change_dir(read);

  free(read);

  return 0;
}
