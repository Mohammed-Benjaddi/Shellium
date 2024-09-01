#include <minishell.h>

void skip_str_inside_quote(char *cmd, int *i, char c)
{
  while(cmd[*i] && cmd[*i] != c)
    *i += 1;
}

bool is_symbol(char c)
{
	if(c == PIPE|| c == IN_RED || c ==  OUT_RED)
		return true;
	return false;
}

size_t reds_counter(char *cmd, t_all *all)
{
  int i;
  size_t counter;

  i = 0;
  counter = 0;
  if(!cmd)  
    return counter;
  while(i < ft_strlen(cmd))
  {
    if(i < ft_strlen(cmd) && (cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE))
    {
      i++;
      counter += 2;
      skip_str_inside_quote(cmd, &i, cmd[i - 1]);
    }
    if(cmd[i] == PIPE)
      counter++;
    else if(i < ft_strlen(cmd) && (cmd[i] == IN_RED || cmd[i] == OUT_RED))
    {
      counter++;
      if (!skip_reds(cmd, &i, cmd[i], all))
        return 0;
    }
    i++;
  }
  return ((counter * 2));
}

bool full_of_spaces(char *buffer)
{
  size_t i;

  i = 0;
  while(buffer[i] && ft_isspace(buffer[i]))
    i++;
  if(i == ft_strlen(buffer))
    return true;
  return false;
}

bool is_incorrect_cmd(char *cmd, int *pipe, t_all *all)
{
  size_t i;

  i = 0;
  if(cmd[i] == PIPE)
  {
    if(!cmd[i + 1])
      return (throw_error("syntax error near unexpected token", all, 258), true);
  }
  if(cmd[i + 1] == PIPE && cmd[i + 2] != PIPE)
  {
    *pipe = -1;
    return false;
  }
  else if(cmd[i + 1] == PIPE && cmd[i + 2] == PIPE)
    return (throw_error("syntax error near unexpected token", all, 258), true);
  return false;
}
