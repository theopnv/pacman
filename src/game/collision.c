#include <errno.h>
#include "game.h"
#include "menu.h"
#include "parameters.h"

int		print_lives(t_exe *exe)
{
  char		lives[2];
  TTF_Font	*font;
  SDL_Surface	*_str, *_int;
  SDL_Color	blue = {0,0,255, 0};
  SDL_Rect	str_pos, int_pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  _str = TTF_RenderText_Solid(font, LIVES, blue);
  str_pos.x = calc_center(_str->w);
  str_pos.y = MARGE_Y + 400;
  lives[0] = exe->game.score.lives + '0';
  lives[1] = '\0';
  _int = TTF_RenderText_Solid(font, lives, blue);
  int_pos.x = str_pos.x + (_str->w - _int->w) / 2;
  int_pos.y = str_pos.y + 75;

  if (!_str || !_int)
    return (err_sdl(TTF_GetError()));
  if (SDL_BlitSurface(_str, NULL, exe->screen, &str_pos) == SYS_ERR
      || SDL_BlitSurface(_int, NULL, exe->screen, &int_pos) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  TTF_CloseFont(font);
  SDL_FreeSurface(_str);
  SDL_FreeSurface(_int);
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
