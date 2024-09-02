/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:54:34 by ael-krid          #+#    #+#             */
/*   Updated: 2024/08/16 14:54:50 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*exp_getlast(t_exp *exp)
{
	t_exp	*tmp;

	tmp = exp;
	if (exp == NULL)
		return (NULL);
	if (exp->next == NULL)
		return (exp);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int	spliter_index(char *string)
{
	int		i;
	char	*str;

	str = string;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			i = i + 1;
			break ;
		}
		i++;
	}
	return (i);
}

t_exp	*exp_new(char *new_line)
{
	t_exp	*new;
	int		index;

	index = spliter_index(new_line);
	new = (t_exp *)malloc(sizeof(t_exp));
	if (!new)
		return (NULL);
	new->variable = ft_strdup(new_line);
	if (new_line[index] == '\0')
		new->value = NULL;
	else
	{
		new->value = ft_strdup(new_line + index);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	exp_addback(t_exp *head, t_exp *new)
{
	t_exp	*tmp;

	tmp = exp_getlast(head);
	tmp->next = new;
	new->prev = tmp;
}
