#include "minishell.h"

int main(int ac, char **av, char **env)
{
  t_shell *shell;

  ft_init(shell);
  char *read = readline("minishell > ");
  if(!read)
    return 0;
  ft_lexer(read, shell);

  return 0;
}
dup2(fd[0], 0);

fd[2];
pip(fd);
int fd = dup(fd[0]);
close(fd);
pip(fd);

dup(fd[0]);