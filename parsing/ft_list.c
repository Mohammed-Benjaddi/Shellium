#include "minishell.h"

static int is_redirection(char *str, char *next)
{
	if(!ft_strcmp(str, ">") && ft_strcmp(next, ">"))
		return 2;
	else if(!ft_strcmp(str, ">") && !ft_strcmp(next, ">"))
		return 3;
	else if(!ft_strcmp(str, "<") && ft_strcmp(next, "<"))
		return 2;
	else if(!ft_strcmp(str, "<") && !ft_strcmp(next, "<"))
		return 3;
	else
		return 0;
}

static size_t count_valid_args(char **args)
{
	size_t i;
	size_t counter;

	i = 0;
	counter = 0;
	while(args[i])
	{
		while(args[i] && is_redirection(args[i], args[i + 1]))
			i += is_redirection(args[i], args[i + 1]);
		if(!args[i])
			break;
		counter++;
		i++;
	}
	return counter;
}

char *catch_arg(char *arg, t_all *all, int i)
{
	char *buffer;
	int index;

  if(get_vars_length(arg) > 0)
		buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	else
		buffer = ft_strdup(arg);
	index = ft_strchr_pro(buffer, DOUBLE_QUOTE, SINGLE_QUOTE, false);
  if (index != -1 && buffer[index - 1] == SINGLE_QUOTE)
    buffer = find_and_remove(buffer, SINGLE_QUOTE);
  else if (index != -1 && buffer[index - 1] == DOUBLE_QUOTE)
    buffer = find_and_remove(buffer, DOUBLE_QUOTE);
	// system("leaks -q minishell");
	return buffer;
}

int get_first_word_index(char *str)
{
	int i;

	i = 0;
	printf("str: %s\n", str);
	while(str[i] && str[i] != ' ')
		i++;
	return i;
}

void handle_var_as_cmd(char **result, char *arg, int *j, t_all *all)
{
	char *buffer;
	char **words;
	int index;
	int i;
	int len;

	i = 0;
	buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	if(!buffer)
		return;
	words = ft_split(buffer, ' ');
	len = get_arr_len(words);
	index = get_first_word_index(buffer);
	if(len == 1)
	{
		result[0] = ft_strdup(words[0]);
		ft_free(words, len);
		free(buffer);
		return;
	}
	result[0] = ft_strndup(buffer, index);
	if(len > 1)
		result[1] = ft_strtok(ft_strdup(buffer + index + 1));
	*j += 1;
	ft_free(words, len);
	free(buffer);
}

char **ft_args_dup(char **args, t_all *all)
{
	int i;
	int j;
	char **result;

	i = -1;
	j = 0;
	if(!count_valid_args(args))
		return NULL;
	result = malloc(sizeof(char *) * (count_valid_args(args) + 2));
	if(!result)
		return NULL;
	while (args[++i])
	{
		while(args[i] && is_redirection(args[i], args[i + 1]))
			i += is_redirection(args[i], args[i + 1]);
		if(!args[i])
			break;
		if(j == 0 && get_vars_length(args[i]) > 0)
			handle_var_as_cmd(result, args[i], &j, all);
		else
			result[j] = catch_arg(args[i], all, i);
		j++;
	}
	result[j] = NULL;
	return result;
}

void free_cmd(t_cmd *cmd)
{
	if(cmd->args)
		ft_free(cmd->args, get_arr_len(cmd->args));
	if(cmd->cmd)
		free(cmd->cmd);
	if(cmd->in_file)
		free(cmd->in_file);
	if(cmd->out_file)
		free(cmd->out_file);
	if(cmd->heredoc_content)
		free(cmd->heredoc_content);
	if(cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	if(cmd->full_path)
		free(cmd->full_path);
	if(cmd->append_file)
		free(cmd->append_file);
}

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
