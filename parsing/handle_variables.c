#include "minishell.h"

char *extract_var_name(char *str, int *i) 
{
  size_t var_len = 0;
  char var_name[1024];

  while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
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
  free(var_name);
  var_name = NULL;
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

  output = NULL;
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
