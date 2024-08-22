/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krid <ael-krid@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:54:34 by ael-krid          #+#    #+#             */
/*   Updated: 2024/08/16 14:54:50 by ael-krid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_word(char *neadle, char *str)
{
	int	i;

	i = 0;
	if (!str || !neadle)
		return (0);
		
	if (!(*str) || !(*neadle))
		return (0);
	while (str[i])
	{
		if (str[i] != neadle[i])
			return (0);
		i++;
	}
	if (neadle[i] != 0)
		return (0);
	return (1);
}


char	*heredoc(char *heredoc_str, int fd, t_all *all)
{
	char	*full_str;
	char	*input;

	full_str = (char *)malloc(1);
	if (!full_str)
		ft_error(all);
	full_str[0] = 0;
	while (1)
	{
		input = readline(">>");
		if (!input)
			exit(0);
		if (!match_word(input, heredoc_str))
		{
			full_str = ft_strjoin(full_str, input);
			full_str = ft_strjoin(full_str, "\n");
		}
		else
			break ;
	}
	return (full_str);
}

void	heredoc_(t_cmd *doc, t_all *all)
{
	char *here_tmp;
	int i;

	doc->heredoc_content = ft_strdup("");
	i = 0;
	while (doc->heredoc_delimiter[i])
	{
		here_tmp = ft_strdup("");
		here_tmp = heredoc(doc->heredoc_delimiter[i], 1, all);
		doc->heredoc_content = ft_strjoin(doc->heredoc_content+i, here_tmp);
		free(here_tmp);
		i++;
	}
 }
void heredoc_child(int *_pipe, t_cmd *cmd, t_all *all)
{
	signal(SIGINT, SIG_DFL);
	close(_pipe[0]);
	heredoc_(cmd , all);
    write(_pipe[1], cmd->heredoc_content, ft_strlen(cmd->heredoc_content));
    close(_pipe[1]);
    exit(0);
}
void heredoc_ing(t_cmd *cmd, t_all *all) 
{
    char *buffer;
	int read_ret;
	pid_t pid;
	
	read_ret = 1;
    int pipefd[2];
    if (pipe(pipefd) == -1) 
		ft_error(all);
    pid = fork();
	if (pid < 0)
		ft_error(all);
    if (pid == 0) 
		heredoc_child(pipefd, cmd, all);
	else
	{
        close(pipefd[1]);
		while (read_ret > 0)
		{
			buffer = (char *) shell_calloc(sizeof(char) , 11);
			if (!buffer)
				ft_error(all);
			buffer[10] = 0;
			read_ret = read(pipefd[0], buffer, 10);
			cmd->heredoc_content = ft_strjoin(cmd->heredoc_content ,buffer  );
			free(buffer);
		}
        close(pipefd[0]);
    }
    waitpid(pid, NULL, 0);
}

void heredoc_check(t_all *all)
{
	t_cmd	*doc;

	doc = all->cmd;
	while (doc != NULL)
	{
		if (doc->heredoc_delimiter != NULL)
			heredoc_ing(doc, all);
		doc = doc->next;
	}
}

