#include	<stdlib.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i = i + 1;
    }
  return(i);
}

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (src[i])
    {
       dest[i] = src[i];
       i = i + 1;
    }
  return (dest);
}

char    	*my_strdup(char *str)
{

  char          *mem;

  mem = malloc(my_strlen(str)+1);
  if (mem == 0)
    {
      return (NULL);
    }
  my_strcpy(mem, str);
  mem[my_strlen(str)] = '\0';
  return (mem);
}
