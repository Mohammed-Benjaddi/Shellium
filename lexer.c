#include "minishell.h"

int ft_isspace(char c)
{
  if((c >= 9 && c <= 13) || c == 32)
    return 1;
  return 0;
}

int find_len(char *str, bool inside_quotes)
{
  int len;

  len = ft_strchr_pro(str + 1, ' ', '|', inside_quotes); 
  if(len != -1)
    return len;
  return ft_strlen(str);
}

char *get_str_in_quotes(char *command, int *i, char c)
{
  int len;
  char *buffer;

  *i += 1;
  len = ft_strchr(command + *i, c);
  // printf("%slen: %d%s\n", CYAN, len, NC);
  
  if(len == -1)
  {
    if(c == SINGLE_QUOTE)
      throw_error("single quote must be closed");
    else
      throw_error("double quote must be closed");
    return NULL;
  }
  buffer = ft_substr(command + *i, 0, len);
  *i += len;
  buffer = find_and_remove(buffer, c);
  // printf("%sbuffer: %s%s\n", GREEN, buffer, NC);
  return buffer;
}

bool str_has_quotes(char *str, char c)
{
  int i;

  i = 0;
  while (str[i])
  {
    if(str[i] == c)
      return true;
    i++;
  }
  return false;
}

char *get_str_without_quotes(char *command, int *i)
{
  int len;
  char *buffer;

  len = find_len(command + *i, false);
  buffer = ft_substr(command, *i, len);

  if(str_has_quotes(buffer, DOUBLE_QUOTE))
    buffer = find_and_remove(buffer, DOUBLE_QUOTE);
  else if(str_has_quotes(buffer, SINGLE_QUOTE))
    buffer = find_and_remove(buffer, SINGLE_QUOTE);
  *i += len;
  return buffer;
}

void create_cmd(t_cmd **head, char **args, int words, int is_pipe)
{
  t_cmd *cmd;

  cmd = ft_lstnew(args, words, is_pipe);
  ft_lstadd_back(head, cmd);
  ft_free(args);
}

char **allocate_args(char *command, int *pipe_idx, int *words, int i)
{
  char **args;

  *pipe_idx = find_pipe_index(command + i); // i = 20
  if(*pipe_idx == -1)
  {
    // printf("%spipe is the lenght%s\n", CYAN, NC);
    *pipe_idx = ft_strlen(command);
  }
  *words = args_counter(command + i, *pipe_idx);
  // printf("%swords: %d%s\n", MAGENTA, *words, NC);
  args = malloc(sizeof(char *) * *words + 1);

  return args;
}

bool is_pipe_after(char *str)
{
  int i;

  i = 0;
  while (str[i] && ft_isspace(str[i]))
    i++;
  if(str[i] == PIPE)
    return true;
  return false;
}

void ft_lexer(char *command, t_cmd **head)
{
  t_lexer lexer;

  lexer.i = 0;
  lexer.length = ft_strlen(command);
  while(lexer.i < lexer.length)
  {
    lexer.j = 0;
    lexer.pipe = 0;
    while (command[lexer.i] && ft_isspace(command[lexer.i]))
      lexer.i++;
    lexer.args = allocate_args(command, &lexer.pipe_idx, &lexer.words, lexer.i);
    if(!lexer.args)
      return;
    while(command[lexer.i] && lexer.j < lexer.words)
    {
      while (command[lexer.i] && ft_isspace(command[lexer.i]))
        lexer.i++;
      // if(command[lexer.i] == PIPE)
      //   printf("%s----> pipe%s\n", GREEN, NC);
      if(command[lexer.i] == '\'')
        lexer.buffer = get_str_in_quotes(command, &lexer.i, SINGLE_QUOTE);
      else if(command[lexer.i] == '\"')
        lexer.buffer = get_str_in_quotes(command, &lexer.i, DOUBLE_QUOTE);
      else
        lexer.buffer = get_str_without_quotes(command, &lexer.i);
      if(lexer.buffer == NULL)
        return;
      if(!ft_strlen(lexer.buffer))
        break;
      lexer.args[lexer.j] = lexer.buffer;
      lexer.j++;
    }
    lexer.args[lexer.j] = NULL;
    if(lexer.words)
    {
      if(is_pipe_after(command + lexer.i))
        lexer.pipe = 1;
      create_cmd(head, lexer.args, lexer.words, lexer.pipe);
    }
    lexer.i++;
  }
}
