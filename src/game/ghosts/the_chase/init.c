#include "the_chase.h"

t_ext     *init_external_elem(const t_coor pos,
			      const t_coor target, char **map)
{
  t_ext   *ext;

  if (!(ext = malloc(sizeof(t_ext))))
    return (NULL);
  ext->pos = pos;
  ext->target = target;
  ext->map = map;
  return (ext);
}

static t_the_chase  *init_in_out(t_the_chase *chase)
{
  int               i;

  i = -1;
  while (++i < STACK_SIZE)
    {
      if (!(chase->in.array[i] = malloc(sizeof(t_cell)))
          || !(chase->out.array[i] = malloc(sizeof(t_cell)))
          || !(chase->in.array[i]->parent = malloc(sizeof(t_cell)))
          || !(chase->out.array[i]->parent = malloc(sizeof(t_cell))))
        return (NULL);
      chase->in.array[i]->cell.y = -1;
      chase->in.array[i]->cell.x = -1;
      chase->in.array[i]->G = 0;
      chase->in.array[i]->H = 0;
      chase->in.array[i]->F = 0;
      chase->out.array[i]->cell.y = -1;
      chase->out.array[i]->cell.x = -1;
    }
  return (chase);
}

t_the_chase   *init_the_chase(const t_ext *ext)
{
  t_the_chase *chase;

  if (!(chase = malloc(sizeof(t_the_chase)))
      || !(chase = init_in_out(chase)))
    return (NULL);
  chase->in.idx = 0;
  chase->out.idx = 0;
  chase->in.array[chase->in.idx]->cell = ext->pos;
  chase->in.array[chase->in.idx]->parent = NULL;
  return (chase);
}
