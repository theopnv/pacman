#include <stdlib.h>
#include <time.h>
#include "menu.h"

static int		mainloop(t_exe *exe)
{
  int			menu_opt;
  const t_options	menu_tab[NB_MENU_OPT] =
    {
      launch_game,
      launch_controls,
      launch_scores,
      launch_credits,
      launch_menu,
      launch_high_score,
      launch_game_over
     };

  get_input(exe);
  if (exe->active[GAME_OVER] == 0)
    aff_bg(exe);
  for (menu_opt = 0; menu_opt < NB_MENU_OPT; menu_opt++)
    if (exe->active[menu_opt] && menu_tab[menu_opt](exe) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  if (SDL_Flip(exe->screen) == SYS_ERR)
    return (err_sdl(SDL_GetError()));

  if (!exe->active[GAME])
    SDL_Delay(MENU_FRAME);
  else
    SDL_Delay(FRAME);
  return (EXIT_SUCCESS);
}

int	main(__attribute__((unused)) int ac,
	     __attribute__((unused)) char **av)
{
  t_exe	exe;

  srand(time(NULL));
  if (init(&exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  while (!exe.exit)
    if (mainloop(&exe) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  free_end(&exe);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
  return (EXIT_SUCCESS);
}