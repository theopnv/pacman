/*
** rev_str.c for  in /home/penava-t/Projects/C/Utils/my-libc
**
** Made by Theo Penavaire
** Login   <penava-t@epitech.net>
**
** Started on  Sat Nov 12 18:38:49 2016 Theo Penavaire
** Last update Sat Nov 12 19:17:04 2016 Theo Penavaire
*/

#include <stdlib.h>
#include "my-libc.h"

char	*rev_str(char *str, const int length)
{
  char	tmp;
  int	start;
  int	end;

  start = 0;
  end = length - 1;
  while (start < end)
    {
      tmp = str[start];
      str[start] = str[end];
      str[end] = tmp;
      ++start;
      --end;
    }
  return (str);
}
