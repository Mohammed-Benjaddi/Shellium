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

// mon, 7:59
int main(int ac, char **av, char **env)
{
  t_all *all;

  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  // all->nums_of_cmds = 1;
  // ft_init(shell);
  using_history();
  // printf("========\n");

  set_lists(all, env);

  while(1)
  {
    printf("%s-> %s", GREEN, NC);
    char *read = readline("minishell > ");
    if(!read || !ft_strlen(read))
      continue;
    add_history(read);
    // set_lists(all, env);
    if(!ft_lexer(read, &all))
      continue;
    // check_args(all, all->cmd);
    print_list(all->cmd);
    all->nums_of_cmds = count_commands(all->cmd);
    // printf("nums of pipes: %zu\n", all->nums_of_cmds);
    // printf("there is %zu pipes\n", all->nums_of_cmds);
    // all->nums_of_cmds = cmds_counter(all->cmd);
    execution(&all, env);
    // get_path(head);
    // free(read);
    // read = NULL;
    ft_lstclear(&all->cmd);
    // system("leaks minishell");
  }
  return 0;
}
