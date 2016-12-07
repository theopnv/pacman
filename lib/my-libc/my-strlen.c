/*
** my-strlen.c for my-strlen in /home/penava-t/Projects/C/Utils/my-libc
**
** Made by Theo Penavaire
** Login   <penava-t@epitech.net>
**
** Started on  Sat Nov 12 16:54:11 2016 Theo Penavaire
** Last update Sat Nov 12 17:04:18 2016 Theo Penavaire
*/

int		my_strlen(const char *str)
{
  const char	*pos;

  pos = str;
  while (*pos++);
  return (pos - str - 1);
}
