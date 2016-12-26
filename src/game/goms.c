#include "game.h"
#include "parameters.h"

static int	new_pos(t_exe * exe)
{
  t_coor	pos;
  static t_coor	old = {-1, -1};

  pos = exe->game.ch[PAC].pos;
  if ((old.y == -1 && old.x == -1)
      || (old.y != pos.y && old.x == pos.x) || (old.y == pos.y && old.x != pos.x))
    {
      old = pos;
      return (1);
    }
  return (0);
}

static void	update_goms(t_exe *exe)
{
  t_coor	pos;

  if (new_pos(exe) && Mix_Playing(0)
      && exe->game.map.goms[exe->game.ch[PAC].pos.y][exe->game.ch[PAC].pos.x] == 0)
    Mix_HaltChannel(0);

  for (pos.y = 0; pos.y < M_HEIGHT; pos.y++)
    for (pos.x = 0; pos.x < M_WIDTH; pos.x++)
      if (exe->game.ch[PAC].pos.x == pos.x
	  && exe->game.ch[PAC].pos.y == pos.y)
	{
  	  if (exe->game.map.goms[pos.y][pos.x] == 1)
  	    {
  	      exe->game.map.goms[pos.y][pos.x] = 0;
  	      ++exe->game.score.catched_goms;
  	      exe->game.score.score += 10;
	      if (!Mix_Playing(0))
	      	Mix_PlayChannel(0, exe->waka, 0);
  	    }
	}
}

static int	aff_goms(t_exe *exe)
{
  int		y, x;
  SDL_Rect	dstrect;
  SDL_Surface	*tmp = NULL;
  SDL_Texture	*gom = NULL;

  dstrect.y = MARGE_Y + TILE / 2;
  dstrect.h = dstrect.w = 5;
  for (y = 0; y < M_HEIGHT; y++)
    {
      dstrect.x = MARGE_X + TILE / 2;
      for (x = 0; x < M_WIDTH; x++)
    	{
    	  if (exe->game.map.goms[y][x] == 1)
    	    {
    	      if (!(tmp = IMG_Load(IMG_GOM)))
    		return (err_sdl(IMG_GetError()));
    	      if (!(gom = SDL_CreateTextureFromSurface(exe->renderer, tmp))
	      	  || SDL_RenderCopy(exe->renderer, gom, NULL, &dstrect) < 0)
    		return (err_sdl(SDL_GetError()));
	      SDL_FreeSurface(tmp);
	      SDL_DestroyTexture(gom);
    	    }
    	  dstrect.x += TILE;
    	}
      dstrect.y += TILE;
    }
  return (EXIT_SUCCESS);
}

int	goms(t_exe *exe)
{
  update_goms(exe);
  if (aff_goms(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
