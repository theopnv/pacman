#include "game.h"

static t_coor	target_pinky(t_exe *exe)
{
  t_coor	target;
  int		y, x;

  y = exe->game.ch[PAC].pos.y;
  x = exe->game.ch[PAC].pos.x;
  switch (exe->game.ch[PAC].state)
    {
      case LEFT:
	target.y = y;
	target.x = x - 5;
	break;
      case UP:
	target.y = y - 5;
	target.x = x;
	break;
      case RIGHT:
	target.y = y;
	target.x = x + 5;
	break;
      case DOWN:
	target.y = y + 5;
	target.x = x;
	break;
      default:
	target.y = y;
	target.x = x;
    }
  return (target);
}

int	pinky(t_exe *exe)
{
  exe->game.ch[PINKY].state = UP;
  exe->game.ch[PINKY].target = target_pinky(exe);
  if (process_ghost(exe, PINKY) == EXIT_FAILURE
      || aff_character(exe, PINKY) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
