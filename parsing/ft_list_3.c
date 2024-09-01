#include "minishell.h"

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

