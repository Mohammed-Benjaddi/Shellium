#include "minishell.h"

int main()
{
  t_shell *shell;

  ft_init(shell);
  char *read = readline("minishell > ");

  t_node *one = ft_lstnew("ls", WORD, D_QUOTE);
  t_node *two = ft_lstnew("cat", WORD, D_QUOTE);
  t_node *three = ft_lstnew("|", PIPE, NORMAL);

  shell->head = ft_lstnew("echo", WORD, NORMAL);
  // ft_lstadd_back(&shell, one);

  // while (shell->head)
  // {
  //   if(shell->head->prev == NULL)
  //     printf("---> null\n");
  //   printf("===> %s\n", shell->head->content);
  //   shell->head = shell->head->next;
  //   // printf("*******\n");
  // }
  
  // printf("after printing\n");
  ft_lexer(read, shell);

  return 0;
}
