#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "game.h"
#include "parameters.h"

static int	init_map(t_exe *exe)
{
  int		y;

  if (!(exe->game.map.map = malloc(sizeof(char *) * M_HEIGHT)))
    return (EXIT_FAILURE);
  for (y = 0; y < M_HEIGHT; y++)
    if (!(exe->game.map.map[y] = calloc(M_WIDTH + 1, sizeof(char))))
      return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	open_map(int *fd)
{
  if ((*fd = open(MAP, O_RDONLY)) == SYS_ERR)
    return (err_c(errno));
  return (EXIT_SUCCESS);
}

static int	read_map(t_exe *exe, const int fd)
{
  int		y;
  char		nl;

  for (y = 0; y < M_HEIGHT; y++)
    {
      if (read(fd, exe->game.map.map[y], M_WIDTH) == SYS_ERR
	  || read(fd, &nl, 1) == SYS_ERR)
	return (err_c(errno));
    }
  return (EXIT_SUCCESS);
}

int	create_map(t_exe *exe)
{
  int	fd;

  if (init_map(exe) == EXIT_FAILURE
      || open_map(&fd) == EXIT_FAILURE
      || read_map(exe, fd) == EXIT_FAILURE
      || close(fd) == SYS_ERR
      || create_accur_map(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
