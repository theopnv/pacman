#include <stdlib.h>
#include "main.h"

int		aff_bg(const t_exe *exe)
{
  SDL_Rect	bg;

  bg.x = bg.y = 0;
  bg.w = WIDTH;
  bg.h = HEIGHT;
  if (SDL_SetRenderDrawColor(exe->renderer, 0, 0, 0, 255) < 0
      || SDL_RenderFillRect(exe->renderer, &bg) < 0)
    return (err_sdl(SDL_GetError()));
  return (EXIT_SUCCESS);
}
