/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-jad <mben-jad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:42:17 by mben-jad          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:22 by mben-jad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strtok(char *str)
{
	char	*result;
	char	*dest;
	int		i;
	int		end;

	end = ft_strlen(str) - 1;
	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '\0')
		return (ft_strdup("\0"));
	while (end > i && ft_isspace(str[end]))
		end--;
	result = (char *)malloc((end - i + 1) + 1);
	if (result == NULL)
		return (NULL);
	dest = result;
	while (i <= end)
	{
		if (!ft_isspace(str[i]) || (dest != result && !ft_isspace(*(dest - 1))))
			*dest++ = str[i];
		i++;
	}
	*dest = '\0';
	free(str);
	return (result);
}

char	*get_only_var(char *str)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	while (str[len] && !is_symbol(str[len]) && str[len] != SPACE
		&& str[len] != SINGLE_QUOTE)
		len++;
	result = ft_substr(str, 0, len);
	return (result);
}

char	*get_var_value(char *str, t_env *env)
{
	char	*var;
	char	*rest;
	char	*result;

	result = NULL;
	var = get_only_var(str);
	rest = ft_strdup(str + ft_strlen(var));
	while (env)
	{
		if (!ft_strcmp(var, env->variable))
		{
			result = ft_strjoin(ft_strdup(env->value), rest);
			break ;
		}
		env = env->next;
	}
	free(str);
	str = NULL;
	free(var);
	if (!result)
		return (rest);
	free(rest);
	return (result);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

char *handle_variables(char *str, t_env *env, size_t length, t_all *all)
{
  size_t i = 0;
  size_t len = strlen(str);
  char output[1024];
  char* var_value;
  output[0] = '\0';

  while (i < len)
  {
    if (str[i] == '$') 
    {
      i++;
      if(i < len && str[i] == '?')
      {

        var_value = ft_itoa(all->exit_status);
        strcat(output, var_value);
        free(var_value);
        var_value = NULL;
        i++;
      }
      else
      {
        char var_name[1024];
        size_t var_len = 0;
        while (i < len && (ft_isalnum(str[i]) || str[i] == '_'))
        var_name[var_len++] = str[i++];
        var_name[var_len] = '\0';
        var_value = get_var_value(ft_strdup(var_name), env);
        strcat(output, var_value);
        free(var_value);
        var_value = NULL;
      }
    }
    else
    {
      size_t j = ft_strlen(output);
      output[j] = str[i];
      output[j + 1] = '\0';
      i++;
    }
  }
  free(var_value);
  free(str);
  str = NULL;
  if(!ft_strlen(output))
    return NULL;
  return ft_strtok(ft_strdup(output));
}
