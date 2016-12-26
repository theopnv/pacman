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

static int	blit_scoring(t_exe *exe, SDL_Surface *s_str, SDL_Surface *s_int,
			     SDL_Rect str_pos, SDL_Rect int_pos)
{
  SDL_Texture	*t_str = NULL, *t_int = NULL;

  if (!s_str || !s_int)
    return (err_sdl(TTF_GetError()));
  if (!(t_str = SDL_CreateTextureFromSurface(exe->renderer, s_str))
      || !(t_int = SDL_CreateTextureFromSurface(exe->renderer, s_int))
      || SDL_RenderCopy(exe->renderer, t_str, NULL, &str_pos) < 0
      || SDL_RenderCopy(exe->renderer, t_int, NULL, &int_pos) < 0)
    return (err_sdl(SDL_GetError()));
  SDL_FreeSurface(s_str);
  SDL_FreeSurface(s_int);
  SDL_DestroyTexture(t_str);
  SDL_DestroyTexture(t_int);
  return (EXIT_SUCCESS);
}

static int	print_level(t_exe *exe)
{
  char		lvl[9/*Max int*/];
  TTF_Font	*font;
  SDL_Surface	*s_str = NULL, *s_int = NULL;
  SDL_Color	blue = {0, 0, 255, 0};
  SDL_Rect	str_pos, int_pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  s_str = TTF_RenderText_Solid(font, LEVEL, blue);
  str_pos.x = calc_center(s_str->w);
  str_pos.y = 100;
  str_pos.h = 50;
  str_pos.w = s_str->w;
  if (exe->game.score.lvl >= INT_MAX)
    exe->game.score.lvl = INT_MAX;
  if (snprintf(lvl, 9, "%d", exe->game.score.lvl) < 0)
    return (err_c(errno));
  s_int = TTF_RenderText_Solid(font, lvl, blue);
  int_pos.x = str_pos.x + (s_str->w - s_int->w) / 2;
  int_pos.y = str_pos.y + 75;
  int_pos.h = 50;
  int_pos.w = s_int->w;
  if (blit_scoring(exe, s_str, s_int, str_pos, int_pos) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  TTF_CloseFont(font);
  return (EXIT_SUCCESS);
}

static int	print_score(t_exe *exe)
{
  char		score[9/*Max int*/];
  TTF_Font	*font;
  SDL_Surface	*s_str, *s_int;
  SDL_Color	blue = {0, 0, 255, 0};
  SDL_Rect	str_pos, int_pos;

  if (!(font = TTF_OpenFont(FONT, 50)))
    return (err_sdl(TTF_GetError()));
  s_str = TTF_RenderText_Solid(font, SCORE, blue);
  str_pos.x = calc_center(s_str->w);
  str_pos.y = 350;
  str_pos.h = 50;
  str_pos.w = s_str->w;
  if (exe->game.score.score >= INT_MAX)
    exe->game.score.score = INT_MAX;
  if (snprintf(score, 9, "%d", exe->game.score.score) < 0)
    return (err_c(errno));
  s_int = TTF_RenderText_Solid(font, score, blue);
  int_pos.x = str_pos.x + (s_str->w - s_int->w) / 2;
  int_pos.y = str_pos.y + 75;
  int_pos.h = 50;
  int_pos.w = s_int->w;
  if (blit_scoring(exe, s_str, s_int, str_pos, int_pos) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  TTF_CloseFont(font);
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
