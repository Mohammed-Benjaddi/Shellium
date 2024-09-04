/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:22:26 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 20:23:10 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	find_len(char *str)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < str_len && str[i] != SPACE && str[i] != PIPE)
	{
		if (i < str_len && (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE))
		{
			i++;
			skip_str_inside_quote(str, &i, str[i - 1]);
		}
		i++;
		if (i < str_len && str[i] == '\0')
		{
			free(str);
			str = NULL;
			return (-1);
		}
	}
	return (i);
}

bool	str_has_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	is_pipe_after(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == PIPE)
		return (true);
	return (false);
}

// bool	no_herdoc_delemiter(char *cmd, int i)
// {
// 	if (!cmd)
// 		false;
// 	while (i >= 0)
// 	{
// 		if (cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE)
// 		{
// 			i--;
// 			while (i >= 0 && cmd[i] != cmd[i + 1])
// 				i--;
// 		}
// 		if (i >= 0 && cmd[i] == PIPE)
// 			return (true);
// 		else if (cmd[i] == '<')
// 		{
// 			i--;
// 			if (i >= 1 && cmd[i] == SPACE && cmd[i - 1] == '<')
// 				return (false);
// 		}
// 		i--;
// 	}
// 	return (true);
// }