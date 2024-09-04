/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:58:07 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 22:23:41 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *str, int *i)
{
	int		var_len;
	char	var_name[1024];

	var_len = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		var_name[var_len++] = str[*i];
		*i += 1;
	}
	var_name[var_len] = '\0';
	return (ft_strdup(var_name));
}

char	*handle_exit_status(t_all *all, char *output, int *i)
{
	char	*var_value;

	var_value = ft_itoa(all->exit_status);
	output = ft_strjoin(output, var_value);
	free(var_value);
	var_value = NULL;
	*i += 1;
	return (output);
}

char	*handle_regular_variable(char *str, int *i, t_env *env, char *output)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(str, i);
	var_value = get_var_value(ft_strdup(var_name), env);
	output = ft_strjoin(output, var_value);
	free(var_value);
	var_value = NULL;
	free(var_name);
	var_name = NULL;
	return (output);
}

char	*append_regular_char(char *output, char c)
{
	char	*result;
	char	*character;

	character = malloc(2);
	character[0] = c;
	character[1] = '\0';
	result = ft_strjoin(output, character);
	free(character);
	character = NULL;
	return (result);
}

char	*handle_variables(char *str, t_env *env, t_all *all)
{
	int		i;
	int		len;
	char	*output;

	i = 0;
	output = NULL;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '\0')
				return (NULL);
			if (i < len && str[i] == '?')
				output = handle_exit_status(all, output, &i);
			else
				output = handle_regular_variable(str, &i, env, output);
		}
		else
			output = append_regular_char(output, str[i++]);
	}
	return (ft_strtok(output));
}
