#include "minishell.h"


size_t pipe_counter(t_cmd *cmd)
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

  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  // all->nums_of_pipes = 1;
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
    all->nums_of_pipes = pipe_counter(all->cmd);
    printf("there is %zu pipes\n", all->nums_of_pipes);
    // exit(1);
    // all->nums_of_pipes = cmds_counter(all->cmd);
    // execution(all, env);

    // get_path(head);
    // free(read);
    // read = NULL;
    ft_lstclear(&all->cmd);
    // system("leaks minishell");
  }
  return 0;
}
