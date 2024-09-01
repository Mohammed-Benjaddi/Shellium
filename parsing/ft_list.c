#include "minishell.h"

int is_redirection(char *str, char *next)
{
	if(!ft_strcmp(str, ">") && ft_strcmp(next, ">"))
		return 2;
	else if(!ft_strcmp(str, ">") && !ft_strcmp(next, ">"))
		return 3;
	else if(!ft_strcmp(str, "<") && ft_strcmp(next, "<"))
		return 2;
	else if(!ft_strcmp(str, "<") && !ft_strcmp(next, "<"))
		return 3;
	else
		return 0;
}

size_t count_valid_args(char **args)
{
	size_t i;
	size_t counter;

	i = 0;
	counter = 0;
	while(args[i])
	{
		while(args[i] && is_redirection(args[i], args[i + 1]))
			i += is_redirection(args[i], args[i + 1]);
		if(!args[i])
			break;
		counter++;
		i++;
	}
	return counter;
}

char *catch_arg(char *arg, t_all *all, int i)
{
	char *buffer;
	int index;

  if(get_vars_length(arg) > 0)
		buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	else
		buffer = ft_strdup(arg);
	index = ft_strchr_pro(buffer, DOUBLE_QUOTE, SINGLE_QUOTE, false);
  if (index != -1 && buffer[index - 1] == SINGLE_QUOTE)
    buffer = find_and_remove(buffer, SINGLE_QUOTE);
  else if (index != -1 && buffer[index - 1] == DOUBLE_QUOTE)
    buffer = find_and_remove(buffer, DOUBLE_QUOTE);
	// system("leaks -q minishell");
	return buffer;
}

int get_first_word_index(char *str)
{
	int i;

	i = 0;
	printf("str: %s\n", str);
	while(str[i] && str[i] != ' ')
		i++;
	return i;
}

void handle_var_as_cmd(char **result, char *arg, int *j, t_all *all)
{
	char *buffer;
	char **words;
	int index;
	int i;
	int len;

	i = 0;
	buffer = handle_variables(arg, all->env, get_vars_length(arg), all);
	if(!buffer)
		return;
	words = ft_split(buffer, ' ');
	len = get_arr_len(words);
	index = get_first_word_index(buffer);
	if(len == 1)
	{
		result[0] = ft_strdup(words[0]);
		ft_free(words, len);
		free(buffer);
		return;
	}
	result[0] = ft_strndup(buffer, index);
	if(len > 1)
		result[1] = ft_strtok(ft_strdup(buffer + index + 1));
	*j += 1;
	ft_free(words, len);
	free(buffer);
}
