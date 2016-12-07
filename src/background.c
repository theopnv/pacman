#include <stdlib.h>
#include "main.h"

int		aff_bg(const t_exe *exe)
{
  int		black;
  SDL_Rect	pos;
  SDL_Surface	*bg;

  pos.x = 0;
  pos.y = 0;
  black = SDL_MapRGB(exe->screen->format, 0, 0, 0);
  bg = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
  if (!bg)
    return (err_sdl(SDL_GetError()));
  if (SDL_FillRect(bg, NULL, black) == SYS_ERR
      || SDL_BlitSurface(bg, NULL, exe->screen, &pos) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  SDL_FreeSurface(bg);
  return (EXIT_SUCCESS);
}
