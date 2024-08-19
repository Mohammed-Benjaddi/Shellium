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

// size_t	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }
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
static void	join_the_two_strings(char *all, char const *s1, char const *s2)
{
	size_t	i;
	int		j;

	i = 0;
	if (s1 != 0)
	{
		while (s1[i])
		{
			all[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
	{
		all[i] = s2[j];
		i++;
		j++;
	}
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*allocated;
// 	size_t	string_len;
// 	size_t	x;

// 	x = 0;
// 	if (s1 != NULL)
// 	{
// 		x = ft_strlen(s1);
// 	}
// 	string_len = x + ft_strlen(s2);
// 	allocated = (char *)malloc(string_len + 1);
// 	if (!allocated)
// 	{
// 		return (NULL);
// 	}
// 	join_the_two_strings(allocated, s1, s2);
// 	allocated[string_len] = '\0';
// 	free(s1);
// 	return (allocated);
// }
// int write_fd(char *str, int fd)
// {
//     while (*str)
//     {
//         if (write(fd,  &(*str), 1) == -1)
//             return (0);
//         str++;
//     }
//     return (1);
// }


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
void *shell_calloc(size_t size , int count)
{
	unsigned char *ret;
	int i;

	if (!count || !size)
		{
			count++;
			size++;
		}
	i = size*count;
	ret = (unsigned char *) malloc(i);

	if (!ret)
		return (NULL);
	i--;
	while(i >=0 )
	{
		ret[i] = 0;
		i--;
	}
	return ((void *) ret);
}
void	heredoc_(t_cmd *doc, t_all *all)
{
	char *here_tmp;
	int i;
	// t_cmd	*doc;


	// doc = all->cmd;
	
	reset_signal_handlers();

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

void heredoc_ing(t_cmd *cmd, t_all *all) 
{
    char *buffer;
	int read_ret;
	
	read_ret = 1;
    int pipefd[2];
    if (pipe(pipefd) == -1) 
	{
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == 0) 
	{
        close(pipefd[0]);
		heredoc_(cmd , all);
        write(pipefd[1], cmd->heredoc_content, ft_strlen(cmd->heredoc_content));
        close(pipefd[1]);
        exit(0);
    } 
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
        // waitpid(pid, NULL, 0);
    }
}

void heredoc_check(t_all *all)
{
	//if (all->cmd->heredoc_delimiter)
	t_cmd	*doc;


	doc = all->cmd;
	while (doc != NULL)
	{
		if (doc->heredoc_delimiter != NULL)
		{
			heredoc_ing(doc, all);
		}
		doc = doc->next;
	}
}

