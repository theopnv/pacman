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
  SDL_Surface	*hs[2];
  char		*pseudo, *score;

  if (!(font = TTF_OpenFont(FONT, 40)))
    return (err_sdl(TTF_GetError()));
  pos[PSD].y = pos[SCR].y = 50;
  for(i = 0; i < NB_HIGH_SCORES; i++)
    {
      pseudo = strdup(exe->game.score.high_scores[i].pseudo);
      score = strdup(exe->game.score.high_scores[i].score);
      hs[PSD] = TTF_RenderText_Solid(font, pseudo, white);
      hs[SCR] = TTF_RenderText_Solid(font, score, white);
      if (!hs[PSD] || !hs[SCR])
	return (err_sdl(TTF_GetError()));
      pos[PSD].x = WIDTH / 2 - (hs[PSD]->w + 30);
      pos[SCR].x = WIDTH / 2 + 30;
      if (SDL_BlitSurface(hs[PSD], NULL, exe->screen, &pos[PSD]) == SYS_ERR
          || SDL_BlitSurface(hs[SCR], NULL, exe->screen, &pos[SCR]) == SYS_ERR)
        return (err_sdl(SDL_GetError()));
      pos[PSD].y += HEIGHT / (NB_HIGH_SCORES + 1);
      pos[SCR].y += HEIGHT / (NB_HIGH_SCORES + 1);
      free(pseudo);
      free(score);
      SDL_FreeSurface(hs[0]);
      SDL_FreeSurface(hs[1]);
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
