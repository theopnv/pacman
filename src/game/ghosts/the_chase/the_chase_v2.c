#include "the_chase.h"

int		map_callback(const int y, const int x)
{
  if (y < 1 || y > 30
      || x < 1 || x > 28)
    return (1);
  return (0);
}

static void	free_the_chase(t_the_chase * chase)
{
  int i;

  for (i = 0; i < STACK_SIZE; i++)
    {
      free(chase->in.array[i]);
      free(chase->out.array[i]);
    }
  free(chase);
}

/*************************************************
* Main function of the chase.
* A* algorithm implemented by Théo Penavaire
* v1.1
*
* TODO:
* Perf improvements:
* - Init struct t_the_chase only once at start.
*
* @param t_coor *position
* @param t_coor *target
* @param char map[y][x]
* @return t_coor * (To free)
**************************************************/

t_coor          *algo_the_chase(const t_coor pos, const t_coor target,
				char **map)
{
  int           end;
  int           lower;
  t_coor        *path;
  t_the_chase   *chase;
  t_ext         *ext;

  if (!(ext = init_external_elem(pos, target, map))
      || !(chase = init_the_chase(ext)))
    return (NULL);
  end = 0;
  while (!end)
    {
      lower = calc_lower(chase);
      if (update_arrays(chase, lower) == EXIT_FAILURE)
      	return (NULL);
      add_in(chase, ext);
      end = end_condition(chase, ext->target);
    }
  if (!(path = flush_path(chase)))
    return (NULL);
  free_the_chase(chase);
  return (path);
}
