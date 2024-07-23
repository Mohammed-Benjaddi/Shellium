#include "minishell.h"

void ft_init(t_shell *shell)
{
  shell->head = NULL;
  shell->size = 0;
  shell->state = NORMAL;
}

t_node *ft_lstnew(char *content, t_type type, t_state state)
{
  t_node *new_node;

  new_node = malloc(sizeof(new_node));
  if(!new_node)
    return NULL;
  new_node->content = content;
  new_node->length = ft_strlen(content);
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->type = type;
  new_node->state = state;
  return new_node;
}

t_node *ft_lstlast(t_node *head)
{
  if(!head)
    return NULL;
  while (head->next != NULL)
    head = head->next;  
  return head;
}

void ft_lstadd_back(t_shell **shell, t_node *new_node)
{
  t_shell *sh;
  t_node *head;

  sh = *shell;
  head = sh->head;
  if(!new_node)
    return;
  if(!head)
  {
    sh->head = new_node;
    return;
  }
  while(head->next != NULL)
    head = head->next;
  head->next = new_node;
  new_node->next = NULL;
  new_node->prev = head;
}

