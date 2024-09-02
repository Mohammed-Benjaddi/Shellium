/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:19:35 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 19:30:29 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_redirection_file(char **args, t_all *all)
{
	int		i;
	char	*in_file;

	i = 0;
	in_file = NULL;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") && ft_strcmp(args[i + 1], "<"))
		{
			if (i == 0 || (i > 0 && ft_strcmp(args[i - 1], "<")))
			{
				if (!args[i + 1])
					return (throw_error("syntax error", all, 258), NULL);
				else
				{
					free(in_file);
					in_file = ft_strdup(args[i + 1]);
				}
			}
		}
		i++;
	}
	return (in_file);
}

void	free_vars_n_error(char **words, char *buffer, t_all *all)
{
	if (words)
		ft_free(words, get_arr_len(words));
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	throw_error("ambiguous redirect", all, 1);
}

char	*get_var(char *str, t_all *all)
{
	char	*buffer;

	buffer = handle_variables(str, all->env, get_vars_length(str), all);
	return (buffer);
}

char	*check_filename(char **args, int i, t_all *all)
{
	char	*buffer;
	char	*result;
	char	**words;
	int		index;

	if (get_vars_length(args[i + 1]) > 0)
	{
		buffer = get_var(args[i + 1], all);
		words = ft_split(buffer, ' ');
		if (!words)
			return (free_vars_n_error(NULL, buffer, all), NULL);
		i = 0;
		while (words[i])
			i++;
		if (i > 1)
			return (free_vars_n_error(words, buffer, all), NULL);
		else
			return (buffer);
	}
	index = ft_strchr_pro(args[i + 1], DOUBLE_QUOTE, SINGLE_QUOTE, false);
	if (index != -1 && args[i + 1][index - 1] == SINGLE_QUOTE)
		return (find_and_remove(ft_strdup(args[i + 1]), SINGLE_QUOTE));
	else if (index != -1 && args[i + 1][index - 1] == DOUBLE_QUOTE)
		return (find_and_remove(ft_strdup(args[i + 1]), DOUBLE_QUOTE));
	return (ft_strdup(args[i + 1]));
}
