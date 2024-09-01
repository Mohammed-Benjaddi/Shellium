#include <minishell.h>

char *get_str_in_quotes(char *command, int *i, char c, t_all *all)
{
  int len;
  char *buffer;
  char *rest;
  char *var_value;

  // *i += 1;
  len = ft_strchr(command + *i + 1, c);
  if(len == -1)
  {
    if(c == SINGLE_QUOTE)
      throw_error("single quote must be closed", all, 1);
    else
      throw_error("double quote must be closed", all, 1);
    return NULL;
  }
  buffer = ft_substr(command + *i, 0, len + 1);
  // if(c == DOUBLE_QUOTE && get_vars_length(buffer) > 0)
  //   buffer = handle_variables(buffer, all->env, get_vars_length(buffer), all);
  *i += len;
  // buffer = find_and_remove(buffer, c);
  return buffer;
}

char *get_str_without_quotes(char *command, int *i, t_env *env, t_all *all)
{
  int len;
  char *buffer;
  int index;

  len = find_len(command + *i, false);
  buffer = ft_substr(command, *i, len);
  *i += len;
  return buffer;
}

int create_cmd(t_all **all, char **args, int words, int is_pipe)
{
  t_cmd *cmd;

  cmd = ft_lstnew(all, args, words, is_pipe);
  if(!cmd)
    return 0;
  ft_lstadd_back(&(*all)->cmd, cmd);
  ft_free(args, get_arr_len(args));
  return 1;
}

char **allocate_args(char *command, int *pipe_idx, int *words, int i)
{
  char **args;

  *pipe_idx = find_pipe_index(command + i);
  if(*pipe_idx == -1)
    *pipe_idx = ft_strlen(command);
  *words = args_counter(command + i, *pipe_idx);
  args = (char **)malloc(sizeof(char *) * (*words + 2));
  if(!args)
    return NULL;
  return args;
}


char *fix_cmd(char *cmd, t_all *all)
{
  int i;
  int j;
  int k;
  char *line;
  char quote;
  int reds_nums = reds_counter(cmd, all);

  if(!reds_nums)
    return cmd;
  i = 0;
  j = 0;
  line = malloc(ft_strlen(cmd) + reds_nums + 10);
  if(!line)
    return NULL;
  while (i < ft_strlen(cmd))
  {
    if(cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE)
    {
      quote = cmd[i];
      k = i;
      line[j++] = cmd[i++];
      while(i < ft_strlen(cmd) && cmd[i] != quote)
        line[j++] = cmd[i++];
      if(i - k == 1)
        line[j++] = ' ';
    }
    else if(((cmd[i] == IN_RED || cmd[i] == OUT_RED || cmd[i] == PIPE)
      && (i > 0 && (cmd[i - 1] != IN_RED || cmd[i - 1] != OUT_RED))))
      {
        line[j++] = ' ';
      }
    else if (i > 0 && (cmd[i - 1] == IN_RED || cmd[i - 1] == OUT_RED) && cmd[i] != SPACE)
      line[j++] = ' ';
    line[j++] = cmd[i++];
  }
  line[j] = '\0';
  return free(cmd),line;
}

