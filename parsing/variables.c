#include <minishell.h>

char *ft_strtok(char *str)
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

    // Skip leading spaces
    // while (*str && isspace((unsigned char)*str)) {
    //     str++;
    // }

    // // If the string is empty after removing leading spaces, return an empty string
    // if (*str == '\0') {
    //     char *result = (char *)malloc(1);
    //     if (result != NULL) {
    //         result[0] = '\0';
    //     }
    //     return result;
    // }

    // // Calculate the length of the string without leading and trailing spaces
    // const char *end = str + strlen(str) - 1;
    // while (end > str && isspace((unsigned char)*end)) {
    //     end--;
    // }
    // size_t new_len = end - str + 1;

    // // Allocate memory for the new string
    // char *result = (char *)malloc(new_len + 1); // +1 for the null terminator
    // if (result == NULL) {
    //     return NULL; // Memory allocation failed
    // }

    // // Copy characters while collapsing spaces
    // char *dest = result;
    // while (str <= end) {
    //     if (!isspace((unsigned char)*str) || (dest != result && !isspace((unsigned char)*(dest - 1)))) {
    //         *dest++ = *str;
    //     }
    //     str++;
    // }

    // // Null-terminate the new string
    // *dest = '\0';

    // return result;

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
  // free(str);
  // str = NULL;
  if(!ft_strlen(output))
    return NULL;
  return ft_strtok(ft_strdup(output));
}







// -----------------------------



















// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

size_t extract_var_name(const char *str, size_t i, char *var_name) {
    size_t var_len = 0;
    while (str[i] && (isalnum((unsigned char)str[i]) || str[i] == '_')) {
        var_name[var_len++] = str[i++];
    }
    var_name[var_len] = '\0';
    return i;
}



char *handle_exit_status(t_all *all, char *output) {
    char *var_value = ft_itoa(all->exit_status);
    strcat(output, var_value);
    free(var_value);
    return output;
}



char *handle_regular_variable(char *var_name, t_env *env, char *output) {
    char *var_value = get_var_value(ft_strdup(var_name), env);
    strcat(output, var_value);
    free(var_value);
    return output;
}



void append_regular_char(char *output, char c) {
    size_t j = strlen(output);
    output[j] = c;
    output[j + 1] = '\0';
}


char *handle_variables_2(char *str, t_env *env, size_t length, t_all *all) {
    size_t i = 0;
    size_t len = strlen(str);
    char output[1024] = { '\0' };

    while (i < len) {
        if (str[i] == '$') {
            i++;
            if (i < len && str[i] == '?') {
                output = handle_exit_status(all, output);
                i++;
            } else {
                char var_name[1024];
                i = extract_var_name(str, i, var_name);
                output = handle_regular_variable(var_name, env, output);
            }
        } else {
            append_regular_char(output, str[i]);
            i++;
        }
    }

    if (!strlen(output)) {
        return NULL;
    }
    return ft_strtok(strdup(output));
}