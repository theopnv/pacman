#include "the_chase.h"

int		logger(const char *, ...);
extern int	g_debug;

/*
* Search cell in array.
*/
static int   in_array(const t_coor cell, t_cell **array)
{
  int         i;

  i = -1;
  while (++i < STACK_SIZE && array[i]->cell.y && array[i]->cell.y != -1)
    if (array[i]->cell.y == cell.y && array[i]->cell.x == cell.x)
      return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

static void   update_distances(t_the_chase *c, const t_coor dir,
			       const t_coor target)
{
  t_coor      H;

  ++c->in.idx;
  /* Record node in open list */
  c->in.array[c->in.idx]->cell = dir;
  /* Make current node its parent */
  c->in.array[c->in.idx]->parent = c->out.array[c->last_out];
  /* G cost : Distance done */
  c->in.array[c->in.idx]->G = c->in.array[c->in.idx]->parent->G + 1;
   /* H cost : Estimated distance left */
   if ((H.x = target.y - dir.y) < 0)
     H.x *= -1;
   if ((H.y = target.x - dir.x) < 0)
     H.y *= -1;
   c->in.array[c->in.idx]->H = H.y + H.y;
   /* F cost : sum */
   c->in.array[c->in.idx]->F = c->in.array[c->in.idx]->G + c->in.array[c->in.idx]->H;
}

/*
* Omg what's that ugly array of integers ?
* - That's just the way Epitech teaches us not to use switches when needed !
*
* List possible directions on a square grid:
* 1. WEST 2. NORTH 3. EAST 4. SOUTH
*/
void     add_in(t_the_chase *chase, const t_ext *ext)
{
  int    i;
  t_coor dir[NDIR] =
    {
      {chase->out.array[chase->last_out]->cell.y,
       chase->out.array[chase->last_out]->cell.x - 1},
      {chase->out.array[chase->last_out]->cell.y - 1,
       chase->out.array[chase->last_out]->cell.x},
      {chase->out.array[chase->last_out]->cell.y,
       chase->out.array[chase->last_out]->cell.x + 1},
      {chase->out.array[chase->last_out]->cell.y + 1,
       chase->out.array[chase->last_out]->cell.x},
    };

  i = -1;
  while (++i < NDIR)
    if (!map_callback(dir[i].y, dir[i].x)
	&& ext->map[dir[i].y][dir[i].x] == SAFE_CELL
	&& in_array(dir[i], chase->out.array) == EXIT_FAILURE)
      update_distances(chase, dir[i], ext->target);
}

int      calc_lower(const t_the_chase *chase)
{
  int    i;
  int    lower;
  int    lower_i;

  i = -1;
  lower_i = 0;
  lower = STACK_SIZE;
  while (chase->in.array[++i]->cell.y != -1 && chase->in.array[i]->F != 0)
    {
      if (chase->in.array[i]->F < lower)
        {
          lower = chase->in.array[i]->F;
          lower_i = i;
          if (chase->in.array[i + 1]->F == 0)
            return (lower_i);
        }
    }
  return (lower_i);
}

int      end_condition(const t_the_chase *chase, const t_coor target)
{
  if (chase->out.array[chase->last_out]->cell.y == target.y
      && chase->out.array[chase->last_out]->cell.x == target.x)
    return (1);
  return (0);
}
