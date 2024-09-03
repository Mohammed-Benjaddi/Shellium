/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:19:17 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 11:41:28 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_reds(char *str, int *i, char c, t_all *all)
{
	int		counter;
	char	redirection;
	int		len;

	counter = 0;
	len = ft_strlen(str);
	while (*i < len && str[*i] && str[*i] == c)
	{
		counter++;
		*i += 1;
		if (counter > 2)
		{
			throw_error("syntax error", all, 258);
			return (0);
		}
	}
	while (*i < len && str[*i] && str[*i] == SPACE)
		*i += 1;
	if (*i < len && is_symbol(str[*i]))
	{
		throw_error("syntax error", all, 258);
		return (0);
	}
	return (1);
}

int	count_len(char *str, int *i, int *length, int str_len)
{
	if (*i < str_len && str[*i] == VAR_SIGN && (*i == 0 || (*i > 0 
				&& str[*i - 1] != BACK_SLASH)))
	{
		while (*i < str_len && str[*i] != DOUBLE_QUOTE && str[*i] != PIPE)
		{
			*i += 1;
			*length += 1;
		}
		return (0);
	}
	return (1);
}

int	get_vars_length(char *str)
{
	int	i;
	int	length;
	int	str_len;

	i = 0;
	length = 0;
	str_len = ft_strlen(str);
	if (!str)
		return (length);
	while (i < str_len)
	{
		skip_spaces(str, &i);
		if (i < str_len && str[i] == SINGLE_QUOTE)
		{
			i++;
			skip_str_inside_quote(str, &i, str[i - 1]);
		}
		if (!count_len(str, &i, &length, str_len))
			break ;
		i++;
	}
	return (length);
}

char	*find_variable(char *str)
{
	int		i;
	int		j;
	char	*vars;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	vars = malloc(get_vars_length(str) + 1);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == VAR_SIGN && str[i - 1] != BACK_SLASH)
		{
			while (str[i] && str[i] != DOUBLE_QUOTE)
			{
				vars[j++] = str[i];
				i++;
			}
		}
		i++;
	}
	return (vars);
}

char	*find_and_remove(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(str) - nums_of_chars(str, c) + 1;
	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * len);
	while (str[i])
	{
		if (str[i] != c)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free(str);
	str = NULL;
	return (res);
}
