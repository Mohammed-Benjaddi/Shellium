#include "minishell.h"

int main(int ac, char **av, char **env)
{
  t_all *all;

  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  all->nums_of_pipes = 1;
  // ft_init(shell);
  using_history();
  while(1)
  {
    printf("%s-> %s", GREEN, NC);
    char *read = readline("minishell > ");
    if(!read)
      continue;
    add_history(read);
    ft_lexer(read, &all);

    print_list(all->cmd);
    // exit(1);
    // all->nums_of_pipes = cmds_counter(all->cmd);
    execution(all, env);

    // get_path(head);
    // free(read);
    // read = NULL;
    ft_lstclear(&all->cmd);
    // system("leaks minishell");
  }
  return 0;
}
