/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:53:15 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 13:08:31 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_str_in_quotes(char *command, int *i, char c, t_all *all)
{
	int		len;
	char	*buffer;
	char	*rest;
	char	*var_value;

	len = ft_strchr(command + *i + 1, c);
	if (len == -1)
	{
		if (c == SINGLE_QUOTE)
			throw_error("single quote must be closed", all, 1);
		else
			throw_error("double quote must be closed", all, 1);
		return (NULL);
	}
	buffer = ft_substr(command + *i, 0, len + 1);
	*i += len + 1;
	printf("buffer ---> %s\n", buffer);
	return (buffer);
}

char	*get_str_without_quotes(char *command, int *i, t_env *env, t_all *all)
{
	int		len;
	char	*buffer;
	int		index;

	len = find_len(command + *i, false);
	buffer = ft_substr(command, *i, len);
	*i += len;
	return (buffer);
}

int	create_cmd(t_all **all, char **args, int words, int is_pipe)
{
	t_cmd	*cmd;

	cmd = ft_lstnew(all, args, words, is_pipe);
	if (!cmd)
		return (0);
	ft_lstadd_back(&(*all)->cmd, cmd);
	ft_free(args, get_arr_len(args));
	return (1);
}

char	**allocate_args(char *command, int *pipe_idx, int *words, int i)
{
	char	**args;

	*pipe_idx = find_pipe_index(command + i);
	if (*pipe_idx == -1)
		*pipe_idx = ft_strlen(command);
	*words = args_counter(command + i, *pipe_idx);
	args = (char **)malloc(sizeof(char *) * (*words + 2));
	if (!args)
		return (NULL);
	return (args);
}
