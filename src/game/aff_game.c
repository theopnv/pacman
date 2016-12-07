#include <SDL/SDL_image.h>
#include "game.h"

extern const t_char	g_assoc_map[NB_TILES];

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
  int		tab;
  int		y, x;
  SDL_Rect	srcrect;
  SDL_Rect	dstrect;

  dstrect.y = MARGE_Y;
  srcrect.y = 0;
  srcrect.w = TILE;
  srcrect.h = TILE;
  for (y = 0; y < M_HEIGHT; y++)
    {
      dstrect.x = MARGE_X;
      for (x = 0; x < M_WIDTH; x++)
	{
	  for (tab = 0; tab < NB_TILES; tab++)
	    if (exe->game.map.map[y][x] == g_assoc_map[tab].key)
	      {
		/* Fill blocks of >= 3x3 with blank tile */
		if (g_assoc_map[tab].key == 'p')
		  srcrect.x = 0;
		else
		  srcrect.x = g_assoc_map[tab].idx * TILE;
	      }
	  if (SDL_BlitSurface(exe->game.maze_sprite, &srcrect, exe->screen, &dstrect) < 0)
	    return (err_sdl(SDL_GetError()));
	  dstrect.x += TILE;
	}
      dstrect.y += TILE;
    }
  return (EXIT_SUCCESS);
}
