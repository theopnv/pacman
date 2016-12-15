#include <errno.h>
#include <SDL/SDL_image.h>
#include "game.h"
#include "menu.h"
#include "parameters.h"

static int	print_pac_live(t_exe *exe, SDL_Rect pos)
{
  SDL_Surface	*surf;

  surf = IMG_Load(PAC_LIVE);
  if (SDL_BlitSurface(surf, NULL, exe->screen, &pos) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  return (EXIT_SUCCESS);
}

int		print_lives(t_exe *exe)
{
  TTF_Font	*font;
  SDL_Surface	*surf;
  SDL_Color	blue = {0,0,255, 0};
  SDL_Rect	pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  if (!(surf = TTF_RenderText_Solid(font, LIVES, blue)))
    return (err_sdl(TTF_GetError()));
  pos.x = calc_center(surf->w);
  pos.y = 580;
  if (SDL_BlitSurface(surf, NULL, exe->screen, &pos) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  if (exe->game.score.lives >= 1)
    {
      pos.y += 75;
      pos.x += 40;
      if (print_pac_live(exe, pos) == EXIT_FAILURE)
    	return (EXIT_FAILURE);
    }

  if (exe->game.score.lives == 2)
    {
      pos.x += 80;
      if (print_pac_live(exe, pos) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

static void	lost_life(t_exe *exe)
{
  --exe->game.score.lives;
  init_game(exe, NOREINIT);
}

int	collision(t_exe *exe)
{
  int	ghosts;

  for (ghosts = BLINKY; ghosts <= CLYDE; ghosts++)
    {
      if (exe->game.ch[PAC].pos.y == exe->game.ch[ghosts].pos.y
	  && exe->game.ch[PAC].pos.x == exe->game.ch[ghosts].pos.x)
	{
	  if (Mix_Playing(0))
	    Mix_HaltChannel(0);
	  lost_life(exe);
	  if (exe->game.score.lives <= 0)
	    init_active(exe,GAME_OVER);
	}
    }
  if (print_lives(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
