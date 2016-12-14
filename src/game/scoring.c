#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include "game.h"
#include "menu.h"
#include "parameters.h"

int	calc_center(const int str_width)
{
  int	aside;

  aside = MARGE_X + M_WIDTH * TILE;
  return (aside + ((WIDTH - aside - str_width) / 2));
}

static int	print_level(t_exe *exe)
{
  char		lvl[9/*Max int*/];
  TTF_Font	*font;
  SDL_Surface	*_str, *_int;
  SDL_Color	blue = {0, 0, 255, 0};
  SDL_Rect	str_pos, int_pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  _str = TTF_RenderText_Solid(font, LEVEL, blue);
  str_pos.x = calc_center(_str->w);
  str_pos.y = MARGE_Y;
  if (exe->game.score.lvl >= INT_MAX)
    exe->game.score.lvl = INT_MAX;
  if (snprintf(lvl, 9, "%d", exe->game.score.lvl) < 0)
    return (err_c(errno));
  _int = TTF_RenderText_Solid(font, lvl, blue);
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

static int	print_score(t_exe *exe)
{
  char		score[9/*Max int*/];
  TTF_Font	*font;
  SDL_Surface	*_str, *_int;
  SDL_Color	blue = {0, 0, 255, 0};
  SDL_Rect	str_pos, int_pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  _str = TTF_RenderText_Solid(font, SCORE, blue);
  str_pos.x = calc_center(_str->w);
  str_pos.y = MARGE_Y + 200;
  if (exe->game.score.score >= INT_MAX)
    exe->game.score.score = INT_MAX;
  if (snprintf(score, 9, "%d", exe->game.score.score) < 0)
    return (err_c(errno));
  _int = TTF_RenderText_Solid(font, score, blue);
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

static void     calc_level(t_exe *exe)
{
  if (exe->game.score.catched_goms != 0
      && exe->game.score.catched_goms % exe->game.score.total_goms == 0)
    {
      ++exe->game.score.lvl;
      if ((exe->game.score.lvl - 1) % 2 == 0)
      	exe->game.score.lives = 2;
      init_goms(exe);
    }
}

int	scoring(t_exe *exe)
{
  calc_level(exe);
  if (print_level(exe) == EXIT_FAILURE
      || print_score(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
