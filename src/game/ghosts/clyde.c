#include "game.h"

static t_coor	far(t_exe *exe)
{
  return (exe->game.ch[PAC].pos);
}

static t_coor	close(t_exe *exe)
{
  return (random_path(exe, CLYDE/*, 1*/));
}

static t_coor	target_clyde(t_exe *exe)
{
  t_coor	target;
  t_coor	pac, clyde;

  pac = exe->game.ch[PAC].pos;
  clyde = exe->game.ch[CLYDE].pos;
  if ((pac.y - clyde.y) + (pac.x - clyde.x) >= 8
      || (pac.y - clyde.y) + (pac.x - clyde.x) <= -8)
    target = far(exe);
  else
    target = close(exe);
  return (target);
}

int	clyde(t_exe *exe)
{
  exe->game.ch[CLYDE].state = UP;
  if (exe->game.score.catched_goms >= exe->game.score.total_goms / 20)
    {
      exe->game.ch[CLYDE].target = target_clyde(exe);
      if (process_ghost(exe, CLYDE) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else
     if (aff_character(exe, CLYDE) == EXIT_FAILURE)
   return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
