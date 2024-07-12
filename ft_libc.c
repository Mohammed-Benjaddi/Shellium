#include "minishell.h"

size_t ft_strlen(char *str)
{
  int i;

  i = 0;
  if(!str)
    return (i);
  while (str[i])
    i++;
  return i;  
}

char *ft_strdup(char *str)
{
  char *buf;
  int i;

  i = 0;
  if(!str)  
    return NULL;
  buf = malloc(sizeof(char) * (ft_strlen(str) + 1));
  while(str[i])
  {
    buf[i] = str[i];
    i++;
  }
  buf[i] = '\0';
  return buf;
}