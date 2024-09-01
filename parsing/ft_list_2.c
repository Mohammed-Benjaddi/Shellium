#include "minishell.h"

bool is_builtin(char *cmd)
{
	if(!cmd)
		return false;
	if(!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") 
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
	return true;
	return false;
}
void fill_node(t_all **all, t_cmd *new_node)
{
	if(new_node->args)
		new_node->cmd = ft_strdup(new_node->args[0]);
	new_node->full_path = get_path(new_node->cmd, (*all)->env);
	if(!new_node->full_path)
	{
		if(is_builtin(new_node->cmd))
		{
			// printf("%s-------> %s%s\n", RED, new_node->cmd, NC);
			return;
		}
		new_node->full_path = get_executable(new_node->cmd);
		if(!new_node->full_path)
			new_node->cmd_not_found = 1;
	}
	// printf("%s------> %s%s\n", CYAN, new_node->cmd, NC);
}

t_cmd	*ft_lstnew(t_all **all, char **args, int args_nbr, int pipe)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->arg_count = args_nbr;

	new_node->args = ft_args_dup(args, *all);
	new_node->in_file = get_input_redirection_file(args, *all);
	new_node->out_file = get_output_redirection_file(args, *all);
	new_node->append_file = get_append_to_file(args, *all);
	new_node->heredoc_delimiter = get_herdoc_delimiter(args, *all);
	new_node->heredoc_content = NULL;
	new_node->pipe = pipe;
	new_node->next = NULL;
	new_node->cmd = NULL;
	new_node->cmd_not_found = false;
	fill_node(all, new_node);
	// system("leaks -q minishell");
	if((*all)->error || (!new_node->args && !new_node->heredoc_delimiter))
	{
		ft_lstclear(&new_node);
		free(new_node);
		return NULL;
	}
	return (new_node);
}

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
		if((*lst)->args)
			ft_free((*lst)->args, get_arr_len((*lst)->args));
		if((*lst)->cmd != NULL)
			free((*lst)->cmd);
		free((*lst)->in_file);
		free((*lst)->out_file);
		if((*lst)->heredoc_delimiter)
			ft_free((*lst)->heredoc_delimiter, get_arr_len((*lst)->heredoc_delimiter));
		free((*lst)->heredoc_content);
		free((*lst)->full_path);
		free((*lst)->append_file);		
		free(*lst);
		*lst = NULL;
		*lst = current;
	}
}
