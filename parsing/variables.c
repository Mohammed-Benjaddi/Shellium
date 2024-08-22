#include <minishell.h>

char *ft_strtok(char *str)
{
  size_t i;
  size_t j;
  size_t len;
  char *result;

  i = 0;
  j = 0;
  len = ft_strlen(str);
  // printf("len : %zu\n", len);
  if(!str)
    return NULL;
  while(str[i] && ft_isspace(str[i]))
    i++;
  while(str[len - 1] && ft_isspace(str[len - 1]))
    len--;
  result = malloc((len - i) + 1);
  while(i < len)
    result[j++] = str[i++];
  result[j] = '\0';
  // printf("%sft_strtok:%s---> %zu%s\n", MAGENTA, result, ft_strlen(result), NC);
  free(str);
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
  // result = malloc(len + 1);
  result = ft_substr(str, 0, len);
  // printf("only variable: %s\n", result);
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
  // free(str);
  free(var);
  if(!result)
    return rest;
  free(rest);
  return result;
}

char *handle_variables(char *str, t_env *env, size_t length)
{
  size_t i;
  char **vars;
  char *var;
  char *result;

  i = 0;
  if(!str)
    return NULL;
  vars = ft_split(str, '$');
  result = NULL;
  while (vars[i])
  {
    vars[i] = find_and_remove(vars[i], DOUBLE_QUOTE);
    // printf("%s---> %s%s\n", RED, vars[i], NC);
    vars[i] = get_var_value(vars[i], env);
    result = ft_strjoin(result, vars[i]);
    i++;
  }
  free(str);
  str = NULL;
  ft_free(vars);
  return result;
}

// char *handle_variables_no_quote(char *str, t_env *env, size_t length)
// {
//   size_t i;
//   char **vars;
//   char *var;
//   char *result;
//   char *rest;

//   i = 0;
//   if(!str)
//     return NULL;
//   // printf("--> %s\n", str + length);
//   if(ft_strlen(str) > length)
//   {
//     rest = ft_strdup(str + length);
//     printf("rest: %s\n", rest);
//     printf("%sgreater than length%zu%s\n", RED, length, NC);
//   }
//   vars = ft_split(str, '$');
//   result = NULL;
//   while (vars[i])
//   {
//     printf("vars ---> %s\n", vars[i]);
//     // vars[i] = find_and_remove(vars[i], DOUBLE_QUOTE);
//     // printf("");
//     vars[i] = get_var_value(vars[i], env);
//     result = ft_strjoin(result, vars[i]);
//     i++;
//   }
//   free(str);
//   str = NULL;
//   ft_free(vars);
//   return result;
// }

// char* process_input(const char* input) {
char *handle_variables_no_quote(char *input, t_env *env, size_t length)
{
  // free();
    size_t len = strlen(input);
    char* output = malloc(len * 3);  // Allocating double the size for safety
    if (!output) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    output[0] = '\0';

    size_t i = 0;
    while (i < len) {
        if (input[i] == '$') {
            // Extract the variable name
            i++;
            char var_name[100];  // Assuming variable names won't exceed 99 characters
            size_t var_len = 0;
            
            while (i < len && (isalnum(input[i]) || input[i] == '_')) {
                var_name[var_len++] = input[i++];
            }
            var_name[var_len] = '\0';

            // Get variable value
            char* var_value = get_var_value(var_name, env);
            strcat(output, var_value);
        } else {
            // Add non-variable characters to output
            size_t j = ft_strlen(output);
            output[j] = input[i];
            output[j + 1] = '\0';
            i++;
        }
    }
  printf("waaaaaaaaaaaaaaaaa3\n");

    return output;
}
