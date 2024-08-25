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
// void check_leaks()
// {
//   system("leaks -q minishell");
// }

void skip_spaces(char *cmd, int *i)
{
  while (cmd[*i] && ft_isspace(cmd[*i]))
    *i += 1;
}

bool is_symbol_in_cmd(char c)
{
  if(c == SLASH || c == BACK_SLASH)
    return true;
  return false;
}

bool is_correct_cmd(char *cmd)
{
  int i;

  i = 0;
  skip_spaces(cmd, &i);
  if(cmd[i] == PIPE)
    return false;
  while(i < ft_strlen(cmd))
  {
    skip_spaces(cmd, &i);
    if(cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE)
    {
      i++;
      skip_str_inside_quote(cmd, &i, cmd[i - 1]);
    }
    else if(cmd[i] == PIPE)
    {
      if(cmd[++i] && cmd[i] == PIPE)
        i++;
      skip_spaces(cmd, &i);
      if(is_symbol_in_cmd(cmd[i]) || cmd[i] == PIPE)
        return false;
    }
    i++;
  }
  return true;
}
void f()
{
  system("leaks -q minishell");
}
int main(int ac, char **av, char **env)
{
  t_all *all;

  all = malloc(sizeof(t_all));
  all->cmd = NULL;
  // all->nums_of_cmds = 1;
  // ft_init(shell);
  using_history();
  set_lists(all, env); // 
  setup_signal_handlers();
  atexit(f);
  while(1)
  {
    char *read = readline("minishell > ");
    if(!read)
    {
      env_exp_lists_clear(all);
      exit(0);
    }
    if (ft_strlen(read))
    {
      add_history(read);
      read = fix_cmd(read);
      if(!is_correct_cmd(read))
        continue;
      if(!ft_lexer(read, &all))
        continue;
        all->nums_of_cmds = count_commands(all->cmd);
      execution(&all, env);
      free(all->_vars->pids);
      free(all->_vars);
      ft_lstclear(&all->cmd);
    }
    else
      free(read);
  }
    return 0;
}
