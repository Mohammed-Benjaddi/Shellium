/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:25:32 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/02 22:26:03 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_s_d_quotes(t_fix_cmd *vars, char *cmd)
{
	vars->quote = cmd[vars->i];
	vars->k = vars->i;
	vars->line[vars->j++] = cmd[vars->i++];
	while (vars->i < ft_strlen(cmd) && cmd[vars->i] != vars->quote)
		vars->line[vars->j++] = cmd[vars->i++];
	if (vars->i - vars->k == 1)
		vars->line[vars->j++] = ' ';
}

void	vars_init(t_fix_cmd *vars, char *cmd, t_all *all)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
	vars->quote = 0;
	vars->reds_nums = reds_counter(cmd, all);
	vars->line = malloc(ft_strlen(cmd) + vars->reds_nums + 10);
}

char	*fix_cmd(char *cmd, t_all *all)
{
	t_fix_cmd	vars;

	vars_init(&vars, cmd, all);
	if (!vars.reds_nums)
		return (cmd);
	vars.line = malloc(ft_strlen(cmd) + vars.reds_nums + 10);
	if (!vars.line)
		return (NULL);
	while (vars.i < ft_strlen(cmd))
	{
		if (cmd[vars.i] == SINGLE_QUOTE || cmd[vars.i] == DOUBLE_QUOTE)
			handle_s_d_quotes(&vars, cmd);
		else if (((cmd[vars.i] == IN_RED || cmd[vars.i] == OUT_RED
					|| cmd[vars.i] == PIPE) && (vars.i > 0 && (cmd[vars.i
						- 1] != IN_RED || cmd[vars.i - 1] != OUT_RED))))
			vars.line[vars.j++] = ' ';
		else if (vars.i > 0 && (cmd[vars.i - 1] == IN_RED || cmd[vars.i
				- 1] == OUT_RED) && cmd[vars.i] != SPACE)
			vars.line[vars.j++] = ' ';
		vars.line[vars.j++] = cmd[vars.i++];
	}
	vars.line[vars.j] = '\0';
	return (free(cmd), vars.line);
}
