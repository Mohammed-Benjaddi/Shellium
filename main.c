#include "minishell.h"

int main(int ac, char **av, char **env)
{
  t_shell *shell;
  t_cmd *head;

  ft_init(shell);
  using_history();
  head = NULL;
  while(1)
  {
    printf("%s-> %s", GREEN, NC);
    char *read = readline("minishell > ");
    if(!read)
      continue;
    add_history(read);
    // printf("read: %s\n", read);
    ft_lexer(read, &head);
    // printf("pipe was found ---> %d\n", find_pipe_index(read));
    // printf("command words ---> %zu\n", args_counter(read, find_pipe_index(read)));
    free(read);

    print_list(head);

    ft_lstclear(&head);
  }
  return 0;
}
