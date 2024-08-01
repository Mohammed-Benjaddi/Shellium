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
    ft_lexer(read, &head);
    // get_path(head);
    free(read);
    print_list(head);
    ft_lstclear(&head);
  }
  return 0;
}
