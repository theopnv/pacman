#include "game.h"

int			aff_character(t_exe *exe, const int id)
{
  SDL_Rect      	srcrect, dstrect;
  SDL_Texture		*tmp = NULL;

  srcrect.x = TILE * exe->game.ch[id].state;
  srcrect.y = 0;
  srcrect.w = dstrect.w = TILE;
  srcrect.h = dstrect.h = TILE;
  dstrect.x = exe->game.ch[id].accur_pos.x + MARGE_X;
  dstrect.y = exe->game.ch[id].accur_pos.y + MARGE_Y;
  if (!(tmp = SDL_CreateTextureFromSurface(exe->renderer, exe->game.ch[id].sprite))
      || SDL_RenderCopy(exe->renderer, tmp, &srcrect, &dstrect) < 0)
    return (err_sdl(SDL_GetError()));
  SDL_DestroyTexture(tmp);
  return (EXIT_SUCCESS);
}

int		aff_map(t_exe *exe)
{
  SDL_Rect	pos;
  SDL_Texture	*tmp = NULL;

  pos.y = MARGE_Y;
  pos.x = 0;
  pos.w = (M_WIDTH + 1) * TILE;
  pos.h = M_HEIGHT * TILE;
  if (!(tmp = SDL_CreateTextureFromSurface(exe->renderer, exe->game.s_map))
      || SDL_RenderCopy(exe->renderer, tmp, NULL, &pos) < 0)
    return (err_sdl(SDL_GetError()));
  SDL_DestroyTexture(tmp);
  return (EXIT_SUCCESS);
}
