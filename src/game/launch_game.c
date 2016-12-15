#include "game.h"
#include "menu.h"

int	launch_game(t_exe *exe)
{
  if (!exe->game.startup)
    {
      init_active(exe, STARTUP);
      exe->game.startup_time = SDL_GetTicks();
    }
  else if (aff_map(exe) == EXIT_FAILURE
      || goms(exe) == EXIT_FAILURE
      || pacman(exe) == EXIT_FAILURE
      || ghosts(exe) == EXIT_FAILURE
      || collision(exe) == EXIT_FAILURE
      || scoring(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
