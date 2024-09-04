/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:17:09 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 23:29:30 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char *cmd, int *i)
{
	while (cmd[*i] && ft_isspace(cmd[*i]))
		*i += 1;
}

void	shell_init(t_all *all, char **env)
{
	using_history();
	set_lists(all, env);
	setup_signal_handlers();
	all->exit_status = 0;
}

void	print_list(t_cmd *head)
{
	int	i;
	int	i;

	i = 0;
	if (!head)
		printf("head is null\n");
	printf("-----------------------------\n");
	while (head)
	{
		i = 0;
		printf("%s --> ", head->cmd);
		while (head->args[i])
		{
			printf("%s{ %s } %s", YELLOW, head->args[i], NC);
			i++;
		}
		printf("%s %s %s", CYAN, head->full_path, NC);
		printf("%s %d %s", RED, head->cmd_not_found, NC);
		// printf("%s %s %s", RED, head->in_file, NC);
		// printf("%s %s %s", GREEN, head->out_file, NC);
		// printf("%s %s %s", RED, head->append_file, NC);
		// printf("%s %d %s", GREEN, head->pipe, NC);
		head = head->next;
	}
	printf("\n-----------------------------\n");
}

int	start_shell(char *read, t_all **all, char **env)
{
	add_history(read);
	if (!is_correct_cmd(read, *all))
	{
		free(read);
		read = NULL;
		return (0);
	}
	read = fix_cmd(read, *all);
	if ((*all)->error || !ft_lexer(read, all) || !(*all)->cmd)
	{
		free(read);
		read = NULL;
		return (0);
	}
	(*all)->nums_of_cmds = count_commands((*all)->cmd);
	(*all)->pipes_num = (*all)->nums_of_cmds - 1;
	// print_list((*all)->cmd);
	if (!(*all)->error)
		execution(all, env);
	free((*all)->_vars->pids);
	free((*all)->_vars);
	free(read);
	read = NULL;
	ft_lstclear(&(*all)->cmd);
	return (1);
}

void	check_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int ac, char **av, char **env)
{
	t_all	*all;
	char	*read;

	all = malloc(sizeof(t_all));
	all->cmd = NULL;
	shell_init(all, env);
	// atexit(check_leaks);
	while (1)
	{
		all->error = false;
		read = readline("minishell > ");
		if (!read)
		{
			env_exp_lists_clear(all);
			exit(0);
		}
		if (ft_strlen(read))
		{
			if (!start_shell(read, &all, env))
			{
				// system("leaks -q minishell");
				continue ;
			}
		}
		else
			free(read);
		// system("leaks -q minishell");
	}
	return (0);
}

// void	check_leaks(void)
// {
// 	system("leaks -q minishell");
// }