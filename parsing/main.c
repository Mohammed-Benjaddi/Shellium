#include "minishell.h"

size_t count_commands(t_cmd *cmd)
{
  size_t counter;

  counter = 0;
  while (cmd)
  {
    cmd = cmd->next;
    counter++;
  }
  return counter;
}

char *get_variable(t_all *all, char *str)
{
	size_t i;
	char *var;
  t_env *env;

	i = 0;
	var = NULL;
  env = all->env;

  while(env)
  {
    // printf("---> %s\n", env->variable);
    if(!ft_strcmp(str, env->variable))
      return ft_strdup(env->value);
      // printf("---> %s\n", env->value);
    env = env->next;
  }
  return ft_strdup("\n");
  // return var;
}

size_t get_varibale_len(char *str)
{
  size_t i;

  i = 0;
  if(!str)
    return i;
  while (str[i] && str[i] != VAR_SIGN)
    i++;
  return i;
}

size_t ft_strlen_var(char *str)
{
  size_t i;

  i = 0;
  if(!str)
    return i;
  while(str[i])
  {
    if(str[i] == BACK_SLASH && str[i + 1] == VAR_SIGN)
      return i;
    i++;
  }
  return i;
}

char *find_variable(char *str, t_all *all)
{
  size_t i;
  size_t j;
  size_t len;
  char *fixed_arg;
  char *var;

  i = 0;
  j = 0;
  len = get_varibale_len(str + ft_strlen_var(str) + 2) + ft_strlen_var(str);
  fixed_arg = malloc(len + 1);

  while(str[i])
  {
    if(str[i] && str[i] == BACK_SLASH)
    {
      i += 1;
      continue;
    }
    else if(str[i] && str[i] == VAR_SIGN)
    {
      // printf("%svariable detected --> %s%s\n", RED, , NC);
      var = get_variable(all, ft_substr(str, i + 1, get_varibale_len(str + i + 1)));
      printf("%s ------> %s%s\n", GREEN, var, NC);
    }
    // fixed_arg[j] = str[i];
    j++;
    i++;
  }
  return NULL;
}

bool is_var(char *str)
{
  size_t i;

  i = 0;
  while(str[i])
  {
    if(str[i] == BACK_SLASH && str[i + 1] == VAR_SIGN)
      return true;
    i++;
  }
  return false;
}

void check_args(t_all *all, t_cmd *cmd)
{
	size_t i;
	size_t j;
	char *fixed_str;
	char *var;

	i = 0;
  j = 0;
  while(cmd)
  {
    while(cmd->args[i])
    {
      if(is_var(cmd->args[i]))
        cmd->args[i] = find_variable(cmd->args[i], all);
      i++;
    }
    cmd = cmd->next;
  }
}

int main(int ac, char **av, char **env)
{
  t_all *all;

  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  // all->nums_of_cmds = 1;
  // ft_init(shell);
  using_history();
  while(1)
  {
    printf("%s-> %s", GREEN, NC);
    char *read = readline("minishell > ");
    if(!read || !ft_strlen(read))
      continue;
    add_history(read);
    set_lists(all, env);
    if(!ft_lexer(read, &all))
      continue;
    check_args(all, all->cmd);
    print_list(all->cmd);
    all->nums_of_cmds = count_commands(all->cmd);
    // printf("nums of pipes: %zu\n", all->nums_of_cmds);
    // printf("there is %zu pipes\n", all->nums_of_cmds);
    // all->nums_of_cmds = cmds_counter(all->cmd);
    execution(&all, env);
    // get_path(head);
    // free(read);
    // read = NULL;

    ft_lstclear(&all->cmd);  
    // system("leaks minishell");
  }
  return 0;
}
