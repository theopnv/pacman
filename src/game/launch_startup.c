#include "menu.h"
#include "game.h"
#include "parameters.h"

static int	print_startup(t_exe *exe)
{
  TTF_Font	*font = NULL;
  SDL_Surface	*surface[2];
  SDL_Color	yellow = {255, 255, 0, 0};
  SDL_Color	cyan = {0, 255, 255, 0};
  SDL_Rect	pos[2];

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  surface[0] = TTF_RenderText_Solid(font, STARTUP_P_ONE, cyan);
  surface[1] = TTF_RenderText_Solid(font, STARTUP_READY, yellow);
  pos[0].x = M_WIDTH + (M_WIDTH * TILE) / 2 - surface[0]->w / 2;
  pos[0].y = HEIGHT / 3;
  pos[1].x = M_WIDTH + (M_WIDTH * TILE) / 2 - surface[1]->w / 2;
  pos[1].y = HEIGHT / 3 * 2;
  if (SDL_BlitSurface(surface[0], NULL, exe->screen, &pos[0]) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  if (SDL_BlitSurface(surface[1], NULL, exe->screen, &pos[1]) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  TTF_CloseFont(font);
  SDL_FreeSurface(surface[0]);
  SDL_FreeSurface(surface[1]);
  return (EXIT_SUCCESS);
}

int		launch_startup(t_exe *exe)
{
  int		actual_time;

  actual_time = SDL_GetTicks();
  if (aff_map(exe) == EXIT_FAILURE
      || goms(exe) == EXIT_FAILURE
      || aff_character(exe, PAC) == EXIT_FAILURE
      || aff_character(exe, BLINKY) == EXIT_FAILURE
      || aff_character(exe, INKY) == EXIT_FAILURE
      || aff_character(exe, PINKY) == EXIT_FAILURE
      || aff_character(exe, CLYDE) == EXIT_FAILURE
      || print_lives(exe) == EXIT_FAILURE
      || scoring(exe) == EXIT_FAILURE
      || print_startup(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (actual_time - exe->game.startup_time > 3000)
    {
      exe->game.startup_time = actual_time;
      init_active(exe, GAME);
      exe->game.startup = 1;
    }
  return (EXIT_SUCCESS);
}
