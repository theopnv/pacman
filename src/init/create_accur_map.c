#include <math.h>
#include "game.h"

static void	fill_accur_map(t_exe *exe, const int y)
{
  static int	small_y = 0;
  int		small_x;
  int		tile_y;
  int		x;

  tile_y = small_y + TILE;
  while (small_y < tile_y)
    {
      x = 0;
      for (small_x = 0; small_x < M_WIDTH * TILE; small_x++)
	{
	  if (small_x != 0 && small_x % TILE == 0)
	    ++x;
	  exe->game.map.accur_map[small_y][small_x] =
	    exe->game.map.map[y][x];
        }
      ++small_y;
    }
}

int	create_accur_map(t_exe *exe)
{
  int	y;

  if (!(exe->game.map.accur_map = malloc(sizeof(char *) * M_HEIGHT * TILE)))
    return (EXIT_FAILURE);
  for (y = 0; y < M_HEIGHT * TILE; y++)
    if (!(exe->game.map.accur_map[y] =
	  calloc(M_WIDTH * TILE + 1, sizeof(char))))
      return (EXIT_FAILURE);
  for (y = 0; y < M_HEIGHT; y++)
    {
      fill_accur_map(exe, y);
    }
  return (EXIT_SUCCESS);
}
