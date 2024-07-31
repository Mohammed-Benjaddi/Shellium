#include "minishell.h"

void throw_error(char *msg)
{
  printf("Error: %s\n", msg);
}

int find_pipe_index(char *str)
{
  int i;
  int s_quotes;
  int d_quotes;

  i = 0;
  s_quotes = 0;
  d_quotes = 0;
  while (str[i])
  {
    if(str[i] == SINGLE_QUOTE)
    {
      s_quotes++;
      i++;
    }
    else if(str[i] == DOUBLE_QUOTE)
    {
      d_quotes++;
      i++;
    }
    if(s_quotes == 2)
      s_quotes = 0;
    if(d_quotes == 2)
      d_quotes = 0;
    if(str[i] == PIPE && s_quotes == 0 && d_quotes == 0)
      return i;
    i++;
  }
  return -1;
}

size_t args_counter(char *str, int len)
{
  int i;
  int s_quote;
  int d_quote;
  size_t words;

  i = 0;
  s_quote = 0;
  d_quote = 0;
  words = 0;
  if(len == -1)
    len = ft_strlen(str);
  while(str[i] && i < len)
  {
    while (str[i] && str[i] == ' ' && i < len)
    {
      // if(str[i] == SINGLE_QUOTE)
      //   s_quote++;
      // else if(str[i] == DOUBLE_QUOTE)
      //   d_quote++;
      // if(s_quote == 2)
      //   s_quote = 0;
      // if(d_quote == 2)
      //   d_quote = 0;
      i++;
    }
    if (str[i] && str[i] != ' ' && s_quote == 0 && d_quote == 0 && i < len)
      words++;
    while (str[i] && str[i] != ' ' && i < len)
    {
      if(str[i] == SINGLE_QUOTE)
        s_quote++;
      else if(str[i] == DOUBLE_QUOTE)
        d_quote++;
      if(s_quote == 2)
        s_quote = 0;
      if(d_quote == 2)
        d_quote = 0;
      i++;
    }
  }
  return words;
}

void ft_free(char **args)
{
  int i;

  i = 0;
  while(args[i])
  {
    free(args[i]);
    i++;
  }
  free(args);
  args = NULL;
}

void print_list(t_cmd *head)
{
  int i;

  i = 0;
  printf("-----------------------------\n");
  while(head)
  {
    int i;

    i = 0;
    while(head->args[i])
    {
      printf("%s - ", head->args[i]);
      i++;
    }
    printf("*******");
    // exit(0);
    head = head->next;
  }
  printf("\n-----------------------------\n");
}

size_t nums_of_chars(char *str, char c)
{
  int i;
  int counter;

  i = 0;
  counter = 0;
  while(str[i])
  {
    if(str[i] == c)
      counter++;
    i++;
  }
  return counter;
}

char *find_and_remove(char *str, char c)
{
  int i;
  size_t len;
  char *res;

  i = 0;
  len = ft_strlen(str) - nums_of_chars(str, c) + 1;
  printf("%sbefore: %s --> %d%s\n", RED, str, len, NC);
  res = malloc(len);
  while(str[i])
  {
    if(str[i] != c)
    {
      res[i] = str[i];
      printf("%s%c%s", YELLOW, str[i], NC);
    }
    i++;
  }
  printf("\n");
  res[i] = '\0';
  printf("%safter: %s%s\n", GREEN, res, NC);
  // free(str);
  return res;
}
