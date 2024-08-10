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
    // all->cmd->full_path = strdup("/usr/bin/env");
    // all->cmd->args[0] = strdup("env");

    // exit(1);
    // all->nums_of_pipes = cmds_counter(all->cmd);
    
    print_list(all->cmd);
    execution(&all, env);
    printf("\t\tafter exec :%p@\n", all->cmd->cmd);
    
    
    //printf("-----||%s|\n\n", all->cmd->full_path);
    // get_path(head);
    // free(read);
    // read = NULL;
    ft_lstclear(&all->cmd);
    
    // system("leaks minishell");
  }
  return 0;
}
