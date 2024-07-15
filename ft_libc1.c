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

char	*ft_substr(char   *s, unsigned int start, size_t len)
{
	int				i;
	unsigned int	slen;
	char			*res;

	i = 0;
	slen = (unsigned int)ft_strlen(s);
	if (!s || start > slen)
		return (ft_strdup(""));
	if (len > (size_t)slen || (len < (size_t)slen && len
			+ (size_t)start > (size_t)slen))
		len = (size_t)slen - (size_t)start;
	res = (char *)malloc(sizeof(char) * (len) + 1);
	if (res == NULL)
		return (NULL);
	while (i < (int)len && s[start + i] != '\0')
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	ft_strlcpy(res + s1_len, s2, s1_len + s2_len + 1);
	return (res);
}

size_t	ft_strlcpy(char *dst,   char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	i;

	i = 0;
	src_size = ft_strlen(src);
	if (dstsize)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_size);
}
