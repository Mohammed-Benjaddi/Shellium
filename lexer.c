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
  if(len == -1)
  {
    if(c == SINGLE_QUOTE)
      throw_error("single quote must be closed");
    else
      throw_error("double quote must be closed");
    return NULL;
  }
  buffer = ft_substr(command + *i, 0, len - 1);
  printf("%s==> %s%s\n", GREEN, buffer, NC);
  *i += len;
  return buffer;
}

char *get_str_without_quotes(char *command, int *i)
{
  int len;
  char *buffer;

  len = find_len(command + *i, false);
  buffer = ft_substr(command, *i, len);
  *i += len;
  return buffer;
}

// char *get_str_in_quotes(char *command, int *i, char c)
// {
//   int len;
//   char *buffer;

//   *i += 1;
//   len = ft_strchr(command + *i, c, true);
//   // printf("===> length: %d\n", len);
//   if(len == -1)
//   {
//     if(c == '\'')
//       throw_error("single quote must be closed");
//     else
//       throw_error("double quote must be closed");
//     return NULL;
//   }
//   buffer = ft_substr(command + *i, 0, len - 1);
//   *i += len;
//   return buffer;
// }

void create_cmd(t_cmd **head, char **args, int words)
{
  t_cmd *cmd;

  cmd = ft_lstnew(args, words);
  ft_lstadd_back(head, cmd);
  ft_free(args);
}

char **allocate_args(char *command, int *pipe_idx, int *words, int i)
{
  char **args;

  *pipe_idx = find_pipe_index(command + i); // i = 20
  if(*pipe_idx == -1)
    *pipe_idx = ft_strlen(command);
  *words = args_counter(command + i, *pipe_idx);
  args = malloc(sizeof(char *) * *words + 1);

  return args;
}

void ft_lexer(char *command, t_cmd **head)
{
  t_lexer lexer;

  lexer.i = 0;
  lexer.length = ft_strlen(command);
  while(lexer.i < lexer.length)
  {
    lexer.j = 0;
    // printf("words: %d\n", lexer.words);
    // printf("length: %zu\n", ft_strlen(command));
    // printf("%scommand + i: %s --- i: %d%s\n", GREEN, command + lexer.i, lexer.i, NC);
    while (command[lexer.i] && ft_isspace(command[lexer.i]))
        lexer.i++;
    lexer.args = allocate_args(command, &lexer.pipe_idx, &lexer.words, lexer.i);
    if(!lexer.args)
      return;
    while(command[lexer.i] && lexer.j < lexer.words)
    {
      while (command[lexer.i] && ft_isspace(command[lexer.i]))
      {
        printf("-> %c", command[lexer.i]);
        lexer.i++;
      }
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
      // printf("buffer: %s --> %zu\n", lexer.buffer, ft_strlen(lexer.buffer));
      // printf("---> %s\n", lexer.buffer);
      lexer.j++;
      // lexer.i++;
    }
    lexer.args[lexer.j] = NULL;
    create_cmd(head, lexer.args, lexer.words);
    lexer.i++;
  }
}
