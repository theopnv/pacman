#include "game.h"

int	blinky(t_exe *exe)
{
  exe->game.ch[BLINKY].target.x = exe->game.ch[PAC].pos.x;
  exe->game.ch[BLINKY].target.y = exe->game.ch[PAC].pos.y;
  exe->game.ch[BLINKY].state = UP;
  if (process_ghost(exe, BLINKY) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
