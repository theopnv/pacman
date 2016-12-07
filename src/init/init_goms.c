#include <errno.h>
#include "game.h"

static int	get_memory_space(t_exe *exe)
{
  int		y;
  int		x;

  if (!(exe->game.map.goms = malloc(sizeof(char *) * M_HEIGHT)))
    return (err_c(errno));
  for (y = 0; y < M_HEIGHT; y++)
    {
      if (!(exe->game.map.goms[y] = calloc(M_WIDTH + 1, sizeof(char))))
	return (err_c(errno));
      for (x = 0; x < M_WIDTH; x++)
	exe->game.map.goms[y][x] = 0;
    }
  return (EXIT_SUCCESS);
}

static int	in_walls(const int y, const int x)
{
  if (y == 9 && ((x >= 0 && x <= 2)
		|| (x >= 9 && x <= 10)
		|| (x >= 17 && x <= 18)
		|| (x >= 25 && x <= 27)))
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static int	central_zone(const int y, const int x)
{
  /* Hard-coded localisation, see later if need to change method */
  if ((x >= 9 && x <= 18)
      && (y == 11
  	  || y == 12
  	  || y == 13
  	  || y == 14
  	  || y == 15
  	  || y == 16
  	  || y == 17))
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static void	fill_goms(t_exe *exe)
{
  int		y, x;

  for (y = 0; y < M_HEIGHT; y++)
    {
      for (x = 0; x < M_WIDTH; x++)
      	{
      	  if (exe->game.map.map[y][x] == 'a'
      	      && central_zone(y, x) == EXIT_FAILURE
      	      && in_walls(y, x) == EXIT_FAILURE)
      	    {
      	      exe->game.map.goms[y][x] = 1;
      	      ++exe->game.score.total_goms;
      	    }
      	}
    }
}

int	init_goms(t_exe *exe)
{
  if (get_memory_space(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  fill_goms(exe);
  return (EXIT_SUCCESS);
}
