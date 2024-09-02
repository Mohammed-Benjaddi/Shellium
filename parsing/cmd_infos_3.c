/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_infos_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:36:20 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 21:43:42 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_output_redirection_file(char **args, t_all *all)
{
	int		i;
	int		fd;
	char	*out_file;

	i = -1;
	out_file = NULL;
	while (args[++i])
	{
		if (!ft_strcmp(args[i], ">"))
		{
			if (!args[i + 1])
				return (throw_error("syntax error", all, 258), NULL);
			else
			{
				if (!ft_strcmp(args[i + 1], ">"))
					return (NULL);
				free(out_file);
				out_file = NULL;
				out_file = check_filename(args, i, all);
				fd = open(out_file, O_CREAT | O_RDWR, 0777);
				close(fd);
			}
		}
	}
	return (out_file);
}

char	*get_append_to_file(char **args, t_all *all)
{
	int		i;
	int		fd;
	char	*file;

	i = 0;
	file = NULL;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") && args[i + 1] && !ft_strcmp(args[i + 1],
				">"))
		{
			i++;
			if (!args[i + 1])
				return (throw_error("syntax error", all, 258), NULL);
			else
			{
				free(file);
				file = check_filename(args, i, all);
				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
				close(fd);
			}
		}
		i++;
	}
	return (file);
}

int	ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

bool	is_incorrect_cmd(char *cmd, int *pipe, t_all *all)
{
	int	i;

	i = 0;
	if (cmd[i] == PIPE)
	{
		if (!cmd[i + 1])
			return (throw_error("syntax error", all, 258), true);
	}
	if (cmd[i + 1] == PIPE && cmd[i + 2] != PIPE)
	{
		*pipe = -1;
		return (false);
	}
	else if (cmd[i + 1] == PIPE && cmd[i + 2] == PIPE)
		return (throw_error("syntax error", all, 258), true);
	return (false);
}
