#include "the_chase.h"

int		logger(const char *);
extern int	g_debug;

t_cell		*init_parent(t_the_chase *chase)
{
    t_cell	*parent;

    if (!(parent = malloc(sizeof(t_cell))))
      return (NULL);
    parent->F = chase->out.array[chase->last_out]->F;
    parent->cell = chase->out.array[chase->last_out]->cell;
    parent->parent = chase->out.array[chase->last_out]->parent;
    return (parent);
}

t_coor		*init_path(const int i)
{
  t_coor	*path;

  if (!(path = malloc(sizeof(t_coor) * STACK_SIZE)))
    return (NULL);
  path[i].y = -1;
  path[i].x = -1;
  return (path);
}

t_coor		*flush_path(t_the_chase *chase)
{
  int		i;
  int		tmp_i;
  t_coor	*path;
  t_coor	tmp[STACK_SIZE];
  t_cell	*parent;

  i = 0;
  parent = init_parent(chase);
  while (parent != NULL)
    {
      tmp[i] = parent->cell;
      parent = parent->parent;
      ++i;
    }
  tmp_i = 0;
  path = init_path(i);
  --i;
  while (i >= 0)
    {
      path[i] = tmp[tmp_i];
      ++tmp_i;
      --i;
    }
  return (path);
}

int		update_arrays(t_the_chase *chase, const int lower)
{
  chase->last_out = chase->out.idx;
  if (chase->out.array[chase->last_out] && chase->out.array[chase->last_out]->cell.y
      && chase->in.array[lower] && chase->in.array[lower]->cell.y)
    {
      if (g_debug)
	logger("INFO|1\n");
      chase->out.array[chase->last_out]->cell = chase->in.array[lower]->cell;
      chase->out.array[chase->last_out]->G = chase->in.array[lower]->G;
      chase->out.array[chase->last_out]->H = chase->in.array[lower]->H;
      chase->out.array[chase->last_out]->F = chase->in.array[lower]->F;
      chase->out.array[chase->last_out]->parent = chase->in.array[lower]->parent;
      if (g_debug)
	logger("INFO|2\n");
      ++chase->out.idx;
      chase->in.array[lower]->F = STACK_SIZE;
      if (g_debug)
	logger("INFO|3\n");
    }
  else
    {
      if (g_debug)
	logger("WARN|Overflow in chase->out or chase->in array\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
