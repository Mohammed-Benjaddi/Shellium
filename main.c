#include "minishell.h"

int main(int ac, char **av, char **env)
{
  t_shell *shell;

  ft_init(shell);
  using_history();
  while(1)
  {
    char *read = readline("minishell > ");
    if(!read)
      continue;
    add_history(read);
    printf("read: %s\n", read);
    // ft_lexer(read, shell);


    free(read);
  }
  

  return 0;
}
