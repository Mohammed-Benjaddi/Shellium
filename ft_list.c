#include "minishell.h"

// void ft_init(t_shell *shell)
// {
//   shell = malloc(sizeof(t_shell));
//   shell->head = NULL;
//   shell->size = 0;
//   shell->state = NORMAL;
// }

char **ft_args_dup(char **args, int args_count)
{
	int i;
	char **result;

	i = 0;
	result = malloc(sizeof(char *) * args_count + 1);
	if(!result)
		return NULL;
	while (args[i])
	{
		result[i] = ft_strdup(args[i]);
		i++;
	}
	result[i] = NULL;
	return result;
}

t_cmd	*ft_lstnew(char **args, int args_nbr, int pipe)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(args[0]);
	new_node->full_path = get_path(new_node->cmd);
	new_node->arg_count = args_nbr;
	new_node->args = ft_args_dup(args, args_nbr);
	new_node->in_file = get_input_redirection_file(new_node->args);
	new_node->out_file = get_output_redirection_file(new_node->args);
	new_node->append_from_file = get_append_from_file(new_node->args);
	new_node->append_to_file = get_append_to_file(new_node->args);
	new_node->heredoc_delimiter = NULL;
	new_node->heredoc_content = NULL;
	new_node->pipe = pipe;
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

void    ft_lstclear(t_cmd **lst)
{
	t_cmd  *current;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		ft_free((*lst)->args);
		free((*lst)->cmd);
		free(*lst);
		*lst = NULL;
		*lst = current;
	}
}
