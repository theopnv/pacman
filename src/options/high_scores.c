#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "menu.h"
#include "parameters.h"

static FILE	*create_high_scores()
{
  int		i;
  FILE		*file;

  if (!(file = fopen(HIGH_SCORES, "w")))
    return (NULL);
  for (i = 0; i < NB_HIGH_SCORES; i++)
    if (!fwrite(HS_LINE, HS_LINE_LENGTH, 1, file))
      return (NULL);
  return (file);
}

static int	flush_high_scores(t_exe *exe, const int i, const char *line)
{
  int		c;
  int		l;

  if (!exe->game.score.high_scores[i].pseudo
      && !exe->game.score.high_scores[i].score)
    {
      if (!(exe->game.score.high_scores[i].pseudo =
	    calloc(PSEUDO_LENGTH, sizeof(char)))
	  || !(exe->game.score.high_scores[i].score =
	    calloc(SCORE_LENGTH, sizeof(char))))
	return (EXIT_FAILURE);
    }
  for (c = 0; line[c] != '\0' && line[c] != ';'; c++)
    exe->game.score.high_scores[i].pseudo[c] = line[c];
  ++c;
  for (l = 0; line[c] != '\0' && line[c] != '\n'; c++, l++)
    exe->game.score.high_scores[i].score[l] = line[c];
  return (EXIT_SUCCESS);
}

int	get_high_scores(t_exe *exe)
{
  FILE	*file;
  int	end = 0;
  int	i = 0;
  char	line[LINE_LENGTH];

  if (!(file = fopen(HIGH_SCORES, "r"))
      && !(file = create_high_scores()))
    return (err_c(errno));
  while (!end)
    {
      if (fgets(line, LINE_LENGTH, file) == NULL)
	{
	  if (i == 0)
	    return (NO_HS);
	  end = 1;
	}
      if (!end && flush_high_scores(exe, i, line) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      ++i;
    }
  fclose(file);
  return (EXIT_SUCCESS);
}

int	is_in_h_scores(t_exe *exe)
{
  int	i;
  int	saved;

  for (i = 0; i < NB_HIGH_SCORES; i++)
    {
      saved = atoi(exe->game.score.high_scores[i].score);
      if (exe->game.score.score > saved)
	return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

static int	display_prompt(t_exe *exe)
{
  SDL_Texture	*text;
  SDL_Color	blue = {0, 0, 255, 0};
  SDL_Rect	pos;
  TTF_Font	*font;

  if (!(font = TTF_OpenFont(FONT, 70)))
    return (err_sdl(TTF_GetError()));
  exe->tmp = TTF_RenderText_Solid(font, PROMPT_HS, blue);
  pos.x = WIDTH / 2 - exe->tmp->w / 2;
  pos.y = HEIGHT / 3;
  pos.h = 70;
  pos.w = exe->tmp->w;

  if (!(text = SDL_CreateTextureFromSurface(exe->renderer, exe->tmp))
      || SDL_RenderCopy(exe->renderer, text, NULL, &pos) < 0)
    return (err_sdl(SDL_GetError()));
  TTF_CloseFont(font);
  SDL_FreeSurface(exe->tmp);
  SDL_DestroyTexture(text);
  return (EXIT_SUCCESS);
}

int		get_score_to_delete(t_exe *exe, const int file)
{
  int		i;
  int		l_score = NOT_IN_HS;
  unsigned int	s;
  char		*line;

  for (i = 0; i < NB_HIGH_SCORES; i++)
    {
      line = get_next_line(file);
      for (s = 0; s < strlen(line); s++)
	{
	  if (s != 0 && line[s - 1] == ';'
	      && atoi(&line[s]) < exe->game.score.score
	      && i < l_score)
	    l_score = i;
	}
      free(line);
    }
  return (l_score);
}

char	*remove_underscores(char *str)
{
  int	i;
  int	end = PSEUDO_LENGTH - 2;

  for (i = end; i >= 0; --i)
    {
      if (str[i] != '\0' && str[i] != '_')
	return (str);
     else
	str[i] = '\0';
    }
   return (str);
}

static int 	display_pseudo(t_exe *exe)
{
  SDL_Texture	*text;
  SDL_Color	blue = {0,0,255,0};
  SDL_Rect	pos;
  TTF_Font	*font;

  if (!(font = TTF_OpenFont(FONT, 70)))
   return (err_sdl(TTF_GetError()));
  exe->tmp = TTF_RenderText_Solid(font, exe->player.pseudo, blue);
  pos.y = HEIGHT / 2;
  pos.x = WIDTH / 2 - exe->tmp->w / 2;
  pos.h = 70;
  pos.w = exe->tmp->w;
  if (!(text = SDL_CreateTextureFromSurface(exe->renderer, exe->tmp))
      || SDL_RenderCopy(exe->renderer, text, NULL, &pos) < 0)
  TTF_CloseFont(font);
  SDL_FreeSurface(exe->tmp);
  SDL_DestroyTexture(text);
  return (EXIT_SUCCESS);
}

int	launch_high_score(t_exe *exe)
{
  get_pseudo(exe);
  if (display_prompt(exe) == EXIT_FAILURE
      || display_pseudo(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exe->active[MENU])
    {
      init_score(exe);
      if (init_player(exe) == EXIT_FAILURE
	  || init_goms(exe) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
