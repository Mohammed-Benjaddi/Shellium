/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:54:34 by ael-krid          #+#    #+#             */
/*   Updated: 2024/09/03 13:33:13 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_exp_list(t_all *all, char *var)
{
	t_exp	*exp;

	exp = all->exp;
	while (exp != NULL)
	{
		if (match_word(var, exp->variable))
		{
			if (exp->prev == NULL)
			{
				if (exp->next != NULL)
					all->exp = exp;
			}
			else if (exp->next == NULL)
				exp->prev->next = NULL;
			else
			{
				exp->prev->next = exp->next;
				exp->next->prev = exp->prev;
			}
			free(exp);
			break ;
		}
		exp = exp->next;
	}
}

t_env	*new_env_(t_exp *exp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(exp->value);
	new->variable = ft_strdup(exp->variable);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*new_empty_env(t_all *all)
{
	t_env	*env_new;

	env_new = (t_env *)malloc(sizeof(t_env));
	if (!env_new)
		ft_error(all);
	env_new->variable = NULL;
	env_new->value = NULL;
	env_new->prev = NULL;
	env_new->next = NULL;
	return (env_new);
}

void	alloc_new_env_node(t_all *all)
{
	t_env	*env_;
	t_env	*env_tmp;
	t_env	*env;
	t_exp	*exp;

	exp = all->exp;
	env_ = all->env;
	while (exp)
	{
		env = env_;
		env_ = new_empty_env(all);
		env_->variable = ft_strdup(exp->variable);
		env_->value = ft_strdup(exp->value);
		env_->prev = env;
		if (env_->prev == NULL)
			env = env_;
		exp = exp->next;
		if (exp && env_)
			env_ = env_->next;
	}
	all->env = env;
}

t_env	*new_env_(t_exp *exp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(exp->value);
	new->variable = ft_strdup(exp->variable);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
void	mirroring_exp_and_env(t_all *all)
{
	t_env	*env;
	t_exp	*exp;

	env = all->env;
	exp = all->exp;
	if (env == NULL && exp != NULL)
		alloc_new_env_node(all);
	while (env != NULL && exp != NULL)
	{
		if (match_word(env->variable, exp->variable) & !match_word(env->value,
				exp->value))
			env->value = exp->value;
		exp = exp->next;
		env = env->next;
	}
}
int	unset_exp(t_all *all, t_exp *exp_, int ret)
{
	t_exp	*exp;

	exp = all->exp;
	while (exp != NULL)
	{
		if (match_word(exp_->variable, exp->variable))
		{
			if (ret == -1)
				return (1);
			exp->value = ft_strdup(exp_->value);
			//if (exp_->value != NULL)
			mirroring_exp_and_env(all);
			return (1);
		}
		exp = exp->next;
		env = env->next;
		if (env == NULL && exp != NULL)
		{
			if (match_word(all->cmd->args[i], env->variable))
			{
				unset_env_list(all, env->variable);
				unset_exp_list(all, all->cmd->args[i]);
				break ;
			}
			env = env->next;
		}
	}
}

