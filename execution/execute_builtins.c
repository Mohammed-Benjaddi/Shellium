/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:54:34 by ael-krid          #+#    #+#             */
/*   Updated: 2024/09/03 13:34:21 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_export(t_all *all)
{
	int	i;

	i = 1;
	while (all->cmd->args[i])
	{
		parse_indetifier(all, all->cmd->args[i]);
		i++;
	}
}
void	handle_exit(t_all *all)
{
	int	exit_num;
	int	exit_;

	ft_write("exit\n", 2);
	if (all->cmd->args[1] != NULL)
	{
		env_exp_lists_clear(all);
		exit(0);
	}
	if (all->cmd->pipe)
		return ;
	exit_ = all->exit_status;
	free_and_exit(all, exit_);
}

int	exec_built_ins(t_all *all)
{
	int	exec;

	exec = 0;
	if (match_word(all->cmd->cmd, "export") && all->cmd->args[1] != NULL)
	{
		handle_export(all);
		exec++;
	}
	if (match_word(all->cmd->cmd, "unset"))
	{
		if (all->cmd->args[1] != NULL)
			unset_env(all);
		exec++;
	}
	if (match_word(all->cmd->cmd, "exit"))
		handle_exit(all);
	if (match_word(all->cmd->cmd, "cd"))
	{
		change_dir(all, all->cmd->args[1]);
		exec++;
	}
	if (exec)
		return (1);
	return (0);
}
