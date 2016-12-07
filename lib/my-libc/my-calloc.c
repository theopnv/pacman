/*
** my_calloc.c for my_calloc in /home/penava-t/rendu/PSU_2015_minishell2
**
** Made by Theo Penavaire
** Login   <penava-t@epitech.net>
**
** Started on  Mon Mar 21 22:08:37 2016 Theo Penavaire
** Last update Sat Nov 12 19:06:49 2016 Theo Penavaire
*/

#include <stdlib.h>

char	*my_calloc(const int length)
{
  int	i;
  char	*result;

  if (!(result = malloc(sizeof(char) * (length + 1))))
    return (NULL);
  i = -1;
  while (++i < length + 1)
    result[i] = '\0';
  return (result);
}
