/*
** logger.c for logger in /home/penava-t/Projects/C/Utils/
**
** Made by Théo Penavaire
** Login   <penava_t@epitech.eu>
**
** Started on  Sat Nov 12 16:48:10 2016 Théo Penavaire
** Last update Mon Nov 14 17:23:34 2016 Théo Penavaire
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define	LOG_FILE		(".log")
#define NB_TYPE			(3)

char						*my_itoa(int);
int							my_strlen(const char *);
int							_char(int, va_list);
int							_str(int, va_list);
int							_int(int, va_list);

typedef struct	s_function
{
	char					key;
	int						(*f)(int, va_list);
}								t_func;

t_func		g_association[NB_TYPE] =
{
	{'c', _char},
	{'s', _str},
	{'d', _int},
};

int					_char(int fd, va_list ap)
{
	char			c;

	c = (char)va_arg(ap, int);
	return (write(fd, &c, 1));
}

int					_str(int fd, va_list ap)
{
	char			*str;

	str = va_arg(ap, char *);
	return (write(fd, str, my_strlen(str)));
}

int					_int(int fd, va_list ap)
{
	char			*str;

	str = my_itoa(va_arg(ap, int));
	if (write(fd, str, my_strlen(str)) < 0)
		{
			free(str);
			return (-1);
		}
	free(str);
	return (EXIT_SUCCESS);
}

int					logger(char	*fmt, ...)
{
	int				fd;
	va_list		ap;
	int				key;

	if ((fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0666)) < 0)
		return (EXIT_FAILURE);
	va_start(ap, fmt);
	while (*fmt)
		{
			if (*fmt == '%')
				{
					++fmt;
					key = -1;
					while (++key < NB_TYPE)
						if (g_association[key].key == *fmt
								&& g_association[key].f(fd, ap) < 0)
							return (EXIT_FAILURE);
				}
			else if (write(fd, &(*fmt), 1) <= 0)
				return (EXIT_FAILURE);
			++fmt;
		}
	close(fd);
	return (EXIT_SUCCESS);
}
