#include <SDL/SDL_image.h>
#include "game.h"

int			aff_character(t_exe *exe, const int id)
{
  SDL_Rect      	srcrect, dstrect;

  srcrect.x = TILE * exe->game.ch[id].state;
  srcrect.y = 0;
  srcrect.w = TILE;
  srcrect.h = TILE;
  dstrect.x = exe->game.ch[id].accur_pos.x + MARGE_X;
  dstrect.y = exe->game.ch[id].accur_pos.y + MARGE_Y;
  if (SDL_BlitSurface(exe->game.ch[id].sprite, &srcrect,
		      exe->screen, &dstrect) < 0)
    return (err_sdl(SDL_GetError()));
  return (EXIT_SUCCESS);
}

int		aff_map(t_exe *exe)
{
  SDL_Rect	pos;

  pos.y = MARGE_Y;
  pos.x = 0;
  if (SDL_BlitSurface(exe->game.s_map, NULL, exe->screen, &pos) < 0)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
