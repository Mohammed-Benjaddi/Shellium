#include "minishell.h"

int check_command(t_lexer *lexer, t_all **all, char *command)
{
  while(command[lexer->i] && lexer->j < lexer->words)
  {
    while (command[lexer->i] && ft_isspace(command[lexer->i]))
      lexer->i++;
    if(command[lexer->i] == SINGLE_QUOTE)
      lexer->buffer = get_str_in_quotes(command, &lexer->i, SINGLE_QUOTE, *all);
    else if(command[lexer->i] == DOUBLE_QUOTE)
      lexer->buffer = get_str_in_quotes(command, &lexer->i, DOUBLE_QUOTE, *all);
    else
      lexer->buffer = get_str_without_quotes(command, &lexer->i, (*all)->env, *all);
    if((*all)->error == true)
      return (free(lexer->buffer), 0);
    if(ft_strlen(lexer->buffer))
    {
      lexer->args[lexer->j] = ft_strdup(lexer->buffer);
      free(lexer->buffer);
      lexer->buffer = NULL;
      lexer->j++;
    }
    else
      lexer->words--;
    }
  return 1;
}

int handle_new_cmd(t_all **all, t_lexer *lexer, char *command)
{
  if(lexer->words && (is_symbol(lexer->args[lexer->words - 1][0]) 
    || lexer->args[lexer->words - 1][0] == BACK_SLASH))
      return (throw_error("syntax error near unexpected token", *all, 258), 0);
  if(lexer->words)
  {
    if(is_pipe_after(command + lexer->i))
      lexer->pipe = 1;
    if (!create_cmd(all, lexer->args, lexer->words, lexer->pipe))
      return 0;
  }
  else
    ft_free(lexer->args, lexer->j);
  return 1;
}



void free_lexer(t_lexer *lexer)
{
  if(lexer->buffer)
    free(lexer->buffer);
  if(lexer->args)
    ft_free(lexer->args, get_arr_len(lexer->args));
}

void init_lexer(t_lexer *lexer, char *command)
{
  lexer->i = 0;
  lexer->args = NULL;
  lexer->length = ft_strlen(command);
}

int ft_lexer(char *command, t_all **all)
{
  t_lexer lexer;

  init_lexer(&lexer, command);
  while(lexer.i < lexer.length)
  {
    lexer.j = 0;
    lexer.pipe = 0;
    while (command[lexer.i] && ft_isspace(command[lexer.i]))
      lexer.i++;
    if(!ft_strlen(command + lexer.i) || is_incorrect_cmd(command + lexer.i, &lexer.pipe, *all))
      return (0);
    lexer.args = allocate_args(command, &lexer.pipe_idx, &lexer.words, lexer.i);
    if(!lexer.args || !check_command(&lexer, all, command))
      return (ft_free(lexer.args, lexer.j), 0);
    lexer.args[lexer.j] = NULL;
    if(!handle_new_cmd(all, &lexer, command))
    {
      free_lexer(&lexer);
      return 0;
    }
    lexer.i++;
    if(lexer.pipe == -1)
      return 1;
  }
  return 1;
}
