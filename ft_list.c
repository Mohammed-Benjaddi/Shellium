#include "minishell.h"

void ft_init(t_shell *shell)
{
  shell = malloc(sizeof(t_shell));
  shell->head = NULL;
  shell->size = 0;
  shell->state = NORMAL;
}

t_cmd	*ft_lstnew(char *content)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = content;
	new_node->next = NULL;
	return (new_node);
}

// t_node *ft_lstlast(t_node *head)
// {
//   if(!head)
//     return NULL;
//   while (head->next != NULL)
//     head = head->next;  
//   return head;
// }

void	ft_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*current;

	current = *cmd;
	if (!new)
		return ;
	if (!current)
	{
		*cmd = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}


