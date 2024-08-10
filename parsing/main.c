#include "minishell.h"


size_t count_commands(t_cmd *cmd)
{
  size_t counter;

  counter = 0;
  while (cmd)
  {
    cmd = cmd->next;
    counter++;
  }
  return counter;
}

int main(int ac, char **av, char **env)
{
  t_all *all;

<<<<<<< HEAD
    all = malloc(sizeof(t_all));
    all->cmd = NULL;
    all->nums_of_pipes = 1;
=======
  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  // all->nums_of_cmds = 1;
>>>>>>> simo
  // ft_init(shell);
  using_history();
  while(1)
  {
    printf("%s-> %s", GREEN, NC);
    char *read = readline("minishell > ");
    if(!read || !ft_strlen(read))
      continue;
    add_history(read);
<<<<<<< HEAD
    ft_lexer(read, &all);
    // all->cmd->full_path = strdup("/usr/bin/env");
    // all->cmd->args[0] = strdup("env");

    // exit(1);
    // all->nums_of_pipes = cmds_counter(all->cmd);
    
    print_list(all->cmd);
    execution(&all, env);
    printf("\t\tafter exec :%p@\n", all->cmd->cmd);
    
    
    //printf("-----||%s|\n\n", all->cmd->full_path);
=======
    if(!ft_lexer(read, &all))
      continue;
    print_list(all->cmd);
    all->nums_of_cmds = count_commands(all->cmd);
    printf("nums of pipes: %zu\n", all->nums_of_cmds);
    // printf("there is %zu pipes\n", all->nums_of_cmds);
    // all->nums_of_cmds = cmds_counter(all->cmd);
    // execution(all, env);

>>>>>>> simo
    // get_path(head);
    // free(read);
    // read = NULL;
    ft_lstclear(&all->cmd);
    
    // system("leaks minishell");
  }
  return 0;
}
