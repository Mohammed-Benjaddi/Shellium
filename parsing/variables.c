#include <minishell.h>

char *ft_strtok_2(char *str)
{
  int i;
  size_t j;
  size_t len;
  char *result;

  i = 0;
  j = 0;
  len = ft_strlen(str);
  if(!str)
    return NULL;
  while(str[i] && ft_isspace(str[i]))
    i++;
  while(str[len - 1] && ft_isspace(str[len - 1]))
    len--;
  result = malloc((len - i) + 1);
  while(i < len)
  {
    result[j++] = str[i++];
    if(str[i] == ' ')
    {
      // if(str[i] == SPACE && str[i + 1] == '\0')
      //   break;
      result[j++] = str[i++];
      skip_spaces(str, &i);
    }
  }
  result[j] = '\0';
  free(str);
  str = NULL;
  printf("%sstrtok: |%s|%s\n", YELLOW, result, NC);
  return result;
  }

char *ft_strtok(char *str)
{
    char *result;
    char *end;
    char *dest;
    while (*str && ft_isspace((unsigned char)*str)) 
      str++;
    if (*str == '\0')
      return ft_strdup("\0");
    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace((unsigned char)*end))
      end--;
    size_t new_len = end - str + 1;
    result = (char *)malloc(new_len + 1);
    if (result == NULL) 
      return NULL;
    dest = result;
    while (str <= end) 
    {
      if (!ft_isspace(*str) || (dest != result && !ft_isspace(*(dest - 1)))) 
        *dest++ = *str;
      str++;
    }
    *dest = '\0';
    // free(str);
    // str = NULL;
    return result;
}

char *get_only_var(char *str)
{
  size_t i;
  size_t len;
  char *result;

  i = 0;
  len = 0;
  while(str[len] && !is_symbol(str[len]) && str[len] != SPACE && str[len] != SINGLE_QUOTE)
    len++;
  result = ft_substr(str, 0, len);
  return result;
}

char *get_var_value(char *str, t_env *env)
{
  char *var;
  char *rest;
  char *result;

  result = NULL;
  var = get_only_var(str);
  rest = ft_strdup(str + ft_strlen(var));
  while(env)
  {
    if(!ft_strcmp(var, env->variable))
    {
      result = ft_strjoin(ft_strdup(env->value), rest);
      break;
    }
    env = env->next;
  }
  free(str);
  str = NULL;
  free(var);
  if(!result)
    return rest;
  free(rest);
  return result;
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

char *extract_var_name(char *str, int *i) 
{
  size_t var_len = 0;
  char var_name[1024];

  while (str[*i] && (ft_isalnum((unsigned char)str[*i]) || str[*i] == '_'))
  {
    var_name[var_len++] = str[*i];
    *i += 1;
  }
  var_name[var_len] = '\0';
  return ft_strdup(var_name);
}

char *handle_exit_status(t_all *all, char *output) 
{
  char *var_value;
  
  var_value = ft_itoa(all->exit_status);
  output = ft_strjoin(output, var_value);
  free(var_value);
  var_value = NULL;
  return output;
}

char *handle_regular_variable(char *str, int *i, t_env *env, char *output) 
{
  char *var_name;
  char *var_value;
  var_name = extract_var_name(str, i);
  var_value = get_var_value(ft_strdup(var_name), env);
  output = ft_strjoin(output, var_value);
  free(var_value);
  var_value = NULL;
  return output;
}

char *append_regular_char(char *output, char c) 
{
  char *result;

  result = malloc(ft_strlen(output) + 2);
  size_t j = ft_strlen(output);
  ft_strlcpy(result, output, j + 1);
  j = ft_strlen(result);
  result[j] = c;
  result[j + 1] = '\0';
  free(output);
  output = NULL;
  return result;
}

char *handle_variables(char *str, t_env *env, size_t length, t_all *all) 
{
  int i = 0;
  size_t len = ft_strlen(str);
  char *output;

  output = ft_strdup("");
  while (i < len) 
  {
    if (str[i] == '$') 
    {
      i++;
      if (i < len && str[i] == '?') 
      {
        output = handle_exit_status(all, output);
        i++;
      }
      else 
        output = handle_regular_variable(str, &i, env, output);
    } 
    else 
      output = append_regular_char(output, str[i++]);
  }
  if (!ft_strlen(output))
      return free(output), NULL;
  return ft_strtok(output);
}
