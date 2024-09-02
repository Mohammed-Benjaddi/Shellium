/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:43:28 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 19:54:24 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_valid_args(char **args)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (args[i])
	{
		while (args[i] && is_redirection(args[i], args[i + 1]))
			i += is_redirection(args[i], args[i + 1]);
		if (!args[i])
			break ;
		counter++;
		i++;
	}
	return (counter);
}

char	*catch_arg(char *arg, t_all *all, int i)
{
	char	*buffer;
	int		index;

	if (get_vars_length(arg) > 0)
		buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	else
		buffer = ft_strdup(arg);
	index = ft_strchr_pro(buffer, DOUBLE_QUOTE, SINGLE_QUOTE, false);
	if (index != -1 && buffer[index - 1] == SINGLE_QUOTE)
		buffer = find_and_remove(buffer, SINGLE_QUOTE);
	else if (index != -1 && buffer[index - 1] == DOUBLE_QUOTE)
		buffer = find_and_remove(buffer, DOUBLE_QUOTE);
	return (buffer);
}

int	get_first_word_index(char *str)
{
	int	i;

	i = 0;
	printf("str: %s\n", str);
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*one_cmd_found(char **words, int len, char *buffer, int *j)
{
	char	*result;

	result = ft_strdup(words[0]);
	ft_free(words, len);
	free(buffer);
	buffer = NULL;
	*j += 1;
	return result;
}

void	handle_var_as_cmd(char **result, char *arg, int *j, t_all *all)
{
	char	*buffer;
	char	**words;
	int		index;
	int		i;
	int		len;

	i = 0;
	buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	if (!buffer)
		return ;
	words = ft_split(buffer, ' ');
	len = get_arr_len(words);
	index = get_first_word_index(buffer);
	if (len == 1)
	{
		result[0] = one_cmd_found(words, len, buffer, j);
		return ;
	}
	result[0] = ft_strndup(buffer, index);
	if (len > 1)
		result[1] = ft_strtok(ft_strdup(buffer + index + 1));
	*j += 2;
	ft_free(words, len);
	free(buffer);
}
