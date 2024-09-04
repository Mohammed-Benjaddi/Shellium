/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:19:52 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 22:21:52 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*isolate_cmd_from_path(char *cmd)
{
	int		i;
	char	*command;
	char	**path;

	i = 0;
	path = ft_split(cmd, '/');
	while (path[i + 1] != NULL)
		i++;
	command = ft_strdup(path[i]);
	ft_free(path, i + 1);
	return (command);
}

static char	**get_all_paths(t_env *env)
{
	char	**all_paths;
	char	*path;

	path = get_var_value(ft_strdup("PATH"), env);
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	free(path);
	path = NULL;
	return (all_paths);
}

char	*search_at_curr_dir(char *cmd)
{
	char	cwd[256];
	char	*path;

	path = NULL;
	getcwd(cwd, sizeof(cwd));
	path = ft_strjoin(ft_strjoin(ft_strdup(cwd), "/"), cmd);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (NULL);
}

char	*get_right_path(char **all_paths, char *cmd, char *line, bool is_path)
{
	int		i;
	char	*path;
	char	*curr_path;

	i = 0;
	path = NULL;
	while (all_paths[i])
	{
		curr_path = ft_strjoin(ft_strdup(all_paths[i]), "/");
		path = ft_strjoin(curr_path, line);
		if (access(path, X_OK) == 0)
		{
			if (correct_path(path, cmd, is_path))
				return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path;
	char	**all_paths;
	char	*line;
	bool	is_path;

	is_path = false;
	path = NULL;
	if (!cmd)
		return (NULL);
	all_paths = get_all_paths(env);
	line = NULL;
	if (cmd[0] && cmd[0] == SLASH && cmd[ft_strlen(cmd) - 1])
	{
		line = isolate_cmd_from_path(cmd);
		is_path = true;
	}
	else
		line = ft_strdup(cmd);
	path = get_right_path(all_paths, cmd, line, is_path);
	ft_free(all_paths, get_arr_len(all_paths));
	free(line);
	if (!path)
		path = search_at_curr_dir(cmd);
	return (path);
}
