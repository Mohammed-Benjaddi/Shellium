// // #include "minishell.h" 
// #include <minishell.h>

// char *get_variable(t_all *all, char *str)
// {
// 	size_t i;
// 	char *var;
//   t_env *env;

// 	i = 0;
// 	var = NULL;
//   env = all->env;
//   while(env)
//   {
//     // printf("---> %s\n", env->variable);
//     if(!ft_strcmp(str, env->variable))
//       return ft_strdup(env->value);
//       // printf("---> %s\n", env->value);
//     env = env->next;
//   }
//   return ft_strdup("\n");
//   // return var;
// }

// size_t get_variable_len(char *str, t_all *all)
// {
//   size_t len;
//   char *var;
//   // t_env *env;

//   if(!str)
//     return 0;
//   printf("getting variable value: %s\n", str);
//   var = get_variable(all, str);
//   len = ft_strlen(var);
//   free(var);
//   return len;
// }

// size_t ft_strlen_var(char *str)
// {
//   size_t i;

//   i = 0;
//   if(!str)
//     return i;
//   // printf("noooooo\n");
//   while(str[i])
//   {
//     if(str[i] == VAR_SIGN)
//       return i;
//     i++;
//   }
//   return i;
// }

// size_t count_vars(char *str)
// {
//   size_t i;
//   size_t counter;

//   i = 0;
//   counter = 0;
//   while(str[i])
//   {
//     if(str[i] == VAR_SIGN && str[i + 1] != VAR_SIGN)
//       counter++;
//     i++;
//   }
//   return counter;
// }

// size_t len_of_var(char *str)
// {
//   size_t i;
//   size_t len;

//   i = 0;
//   len = 0;
//   if(!str)
//     return len;
//   while (str[i])
//   {
//     if(str[i] == VAR_SIGN)
//     {
//       i++;
//       break;
//     }
//     i++;
//   }
//   while(str[i] && str[i] != VAR_SIGN)
//   {
//     len++;
//     i++;
//   }
//   printf("%s length returned: %zu%s\n", RED, len, NC);
//   return len;
// }

// char *find_variable(char *str, t_all *all)
// {
//   size_t i;
//   size_t j;
//   size_t len;
//   char *fixed_arg;
//   char *var;
//   size_t nums_of_vars;

//   i = 0;
//   j = 0;
//   len = 0;
//   nums_of_vars = count_vars(str);
//   // printf("==> str len: %zu\n", ft_strlen_var(str) + get_variable_len(str + ft_strlen_var(str) + 1, all));
//   // printf("==> nums of vars: %zu\n", count_vars(str));

//   // len = ft_strlen_var(str) + get_variable_len(str + ft_strlen_var(str) + 2);
//   while(i < nums_of_vars)
//   {
//     len += ft_strlen_var(str) + get_variable_len(str + ft_strlen_var(str) + 1, all);
//     j += len_of_var(str + j);
//     printf("-----> %zu ----- %zu\n", j, len);
//     i++;
//   }
  
//   printf("%slen: %zu%s\n", MAGENTA, len, NC);

//   fixed_arg = malloc(len + 1);
//   // printf("length allocated ---> %zu\n", len);


//   // while(str[i])

//   return NULL;
// }

// bool is_var(char *str)
// {
//   size_t i;

//   i = 0;
//   while(str[i])
//   {
//     if(str[i] == VAR_SIGN && str[i] != BACK_SLASH)
//       return true;
//     i++;
//   }
//   return false;
// }

// void check_args(t_all *all, t_cmd *cmd)
// {
// 	size_t i;
// 	size_t j;
// 	char *fixed_str;
// 	char *var;

// 	i = 0;
//   j = 0;
//   while(cmd)
//   {
//     while(cmd->args[i])
//     {
//       if(is_var(cmd->args[i]))
//       {
//         printf("%s----------------> variable detected%s\n", GREEN, NC);
//         // return;
//         cmd->args[i] = find_variable(cmd->args[i], all);
//       }
//       i++;
//     }
//     cmd = cmd->next;
//   }
// }