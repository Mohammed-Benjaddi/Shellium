/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_infos_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:35:38 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 17:31:22 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	correct_path(char *path, char *cmd, bool is_path)
{
	if (is_path)
	{
		if (!ft_strcmp(path, cmd))
			return (true);
		return (false);
	}
	return (true);
}

int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

static int	get_delimiters_len(char **args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<"))
			len++;
		i++;
	}
	return (len);
}

char	*get_delimiter(char *arg)
{
	int		index;
	char	*buffer;

	buffer = find_and_remove(ft_strdup(arg), DOUBLE_QUOTE);
	buffer = find_and_remove(buffer, SINGLE_QUOTE);
	return (buffer);
}

char	**get_herdoc_delimiter(char **args, t_all *all)
{
	int		i;
	int		len;
	char	**delimiters;

	i = 0;
	len = get_delimiters_len(args);
	if (!len)
		return (NULL);
	delimiters = malloc(sizeof(char *) * (len + 1));
	i = 0;
	len = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "<") && !ft_strcmp(args[i + 1], "<"))
		{
			i++;
			if (!args[i + 1])
				return (throw_error("syntax error", all, 258), NULL);
			else
				delimiters[len++] = get_delimiter(args[i + 1]);
		}
		i++;
	}
	delimiters[len] = NULL;
	return (delimiters);
}
