/*
** my-itoa.c for my-itoa in /home/penava-t/Projects/C/Utils
**
** Made by Theo Penavaire
** Login   <penava-t@epitech.net>
**
** Started on  Sat Nov 12 18:23:01 2016 Theo Penavaire
** Last update Mon Nov 14 17:19:54 2016 Theo Penavaire
*/

#include "my-libc.h"

static char	*zero(char *str)
{
  str[0] = '0';
  str[1] = '\0';
  return (str);
}

char	*my_itoa(int nb)
{
  char	*str;
  int	i;
  int	is_neg;
  int	remain;

  i = 0;
  is_neg = 0;
  str = my_calloc(12);
  if (nb == 0)
    return (zero(str));
  if (nb < 0)
    {
      is_neg = 1;
      nb = -nb;
    }
  while (nb != 0)
    {
      remain = nb % 10;
      str[i++] = (remain > 9) ? (remain - 10) + 'a' : remain + '0';
      nb /= 10;
    }
  if (is_neg)
    str[i++] = '-';
  return (rev_str(str, i));
}
