#include "game.h"

static t_coor	target_inky(t_exe *exe)
{
  t_coor	target;

  target.y = -1 * (exe->game.ch[BLINKY].pos.y - exe->game.ch[PAC].pos.y);
  target.x = -1 * (exe->game.ch[BLINKY].pos.x - exe->game.ch[PAC].pos.x);
  target.x += exe->game.ch[PAC].pos.x;
  target.y += exe->game.ch[PAC].pos.y;
  return (target);
}

int	inky(t_exe *exe)
{
  exe->game.ch[INKY].state = UP;
  /* Inky starts when pac ate 30 goms */
  if (exe->game.score.catched_goms >= 30)
    {
      exe->game.ch[INKY].target = target_inky(exe);
      if (process_ghost(exe, INKY) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else
    if (aff_character(exe, INKY) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
