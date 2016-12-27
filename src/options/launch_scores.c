#include <errno.h>
#include <string.h>
#include "main.h"
#include "parameters.h"

void	free_high_scores(t_exe *exe)
{
  int	i;

  for (i = 0; i < NB_HIGH_SCORES; i++)
    {
      if (exe->game.score.high_scores[i].pseudo)
	free(exe->game.score.high_scores[i].pseudo);
      if (exe->game.score.high_scores[i].score)
	free(exe->game.score.high_scores[i].score);
    }
}

static int	print_high_scores(t_exe *exe)
{
  int		i;
  TTF_Font	*font;
  SDL_Color	white = { 255, 255, 255, 0 };
  SDL_Rect	pos[2];
  SDL_Surface	*s_hs[2];
  SDL_Texture	*t_hs[2];
  char		*pseudo, *score;

  if (!(font = TTF_OpenFont(FONT, 40)))
    return (err_sdl(TTF_GetError()));
  pos[PSD].y = pos[SCR].y = 50;
  pos[PSD].h = 40;
  pos[SCR].h = 40;
  for(i = 0; i < NB_HIGH_SCORES; i++)
    {
      pseudo = strdup(exe->game.score.high_scores[i].pseudo);
      score = strdup(exe->game.score.high_scores[i].score);
      s_hs[PSD] = TTF_RenderText_Solid(font, pseudo, white);
      s_hs[SCR] = TTF_RenderText_Solid(font, score, white);
      if (!s_hs[PSD] || !s_hs[SCR])
	return (err_sdl(TTF_GetError()));
      pos[PSD].x = WIDTH / 2 - (s_hs[PSD]->w + 30);
      pos[PSD].w = s_hs[PSD]->w;
      pos[SCR].x = WIDTH / 2 + 30;
      pos[SCR].w = s_hs[SCR]->w;

      if (!(t_hs[PSD] = SDL_CreateTextureFromSurface(exe->renderer,
	    s_hs[PSD]))
	  || !(t_hs[SCR] = SDL_CreateTextureFromSurface(exe->renderer,
	    s_hs[SCR]))
	  || SDL_RenderCopy(exe->renderer, t_hs[PSD], NULL, &pos[PSD]) < 0
	  || SDL_RenderCopy(exe->renderer, t_hs[SCR], NULL, &pos[SCR]) < 0)
	return (err_sdl(SDL_GetError()));
      pos[PSD].y += HEIGHT / (NB_HIGH_SCORES + 1);
      pos[SCR].y += HEIGHT / (NB_HIGH_SCORES + 1);
      free(pseudo);
      free(score);
      SDL_FreeSurface(s_hs[PSD]);
      SDL_FreeSurface(s_hs[SCR]);
      SDL_DestroyTexture(t_hs[PSD]);
      SDL_DestroyTexture(t_hs[SCR]);
    }
  TTF_CloseFont(font);
  return (EXIT_SUCCESS);
}

int	launch_scores(t_exe *exe)
{
  if (get_high_scores(exe) == EXIT_FAILURE
      || print_high_scores(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
