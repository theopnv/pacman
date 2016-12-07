#include <string.h>
#include "menu.h"
#include "parameters.h"

static void	free_controls(t_aff_controls *aff)
{
  int		i;

  TTF_CloseFont(aff->font);
  for (i = 0; i < NB_DIR; i++)
    {
      SDL_FreeSurface(aff->text[0][i]);
      SDL_FreeSurface(aff->text[1][i]);
    }
}

static void	free_help(TTF_Font *font, SDL_Surface **surf)
{
  int		i;

  TTF_CloseFont(font);
  for (i = 0; i < NB_MSG_CONTROLS; i++)
    SDL_FreeSurface(surf[i]);
}

static int	aff_help(t_exe *exe)
{
  int		h;
  TTF_Font	*font;
  SDL_Surface	*help[NB_MSG_CONTROLS];
  SDL_Color	white = {255, 255, 255, 0};
  SDL_Rect	pos;
  const char	*msg[NB_MSG_CONTROLS] =
  {CONTROLS_HELP, CONTROLS_ASSIGN, CONTROLS_WARNING};

  if (!(font = TTF_OpenFont(FONT, 30)))
    return (err_sdl(TTF_GetError()));
  pos.y = HEIGHT - 150;
  for (h = 0; h < NB_MSG_CONTROLS; h++)
    {
      help[h] = TTF_RenderText_Solid(font, msg[h], white);
      pos.x = WIDTH / 2 - help[h]->w / 2;
      if (SDL_BlitSurface(help[h], NULL, exe->screen, &pos) == SYS_ERR)
	return (err_sdl(SDL_GetError()));
      pos.y += 50;
    }
  free_help(font, help);
  return (EXIT_SUCCESS);
}

static char	*get_key(t_exe *exe, const int i)
{
  char		*key_tmp;
  char		*key;

  key_tmp = SDL_GetKeyName(exe->param.controls[i].key.keysym.sym);
  if (!(key = calloc(strlen(key_tmp) + 5, sizeof(char))))
    return (NULL);
  key = strcpy(key, "< ");
  key = strcat(key, key_tmp);
  key = strcat(key, " >");
  return (key);
}

static int	render_text(t_aff_controls *aff, const int i,
			    t_exe *exe, const int selected)
{
  SDL_Color	white = {255, 255, 255, 0};
  SDL_Color	red = {255, 0, 0, 0};
  char		*key;

  const char	*options[NB_DIR] =
  {"LEFT", "UP", "RIGHT", "DOWN", "PAUSE"};

  key = get_key(exe, i);
  if (i != selected)
    {
      aff->text[0][i] = TTF_RenderText_Solid(aff->font, options[i], white);
      aff->text[1][i] = TTF_RenderText_Solid(aff->font, key, white);
    }
  else
    {
      aff->text[0][i] = TTF_RenderText_Solid(aff->font, options[i], red);
      aff->text[1][i] = TTF_RenderText_Solid(aff->font, key, red);
    }
  free(key);
  if (!aff->text[0][i] || !aff->text[1][i])
    return (err_sdl(TTF_GetError()));
  return (EXIT_SUCCESS);
}

static int		aff_controls_panel(t_exe *exe, const int selected)
{
  int			i = -1;
  t_aff_controls	aff;
  SDL_Rect		pos[2];

  if (!(aff.font = TTF_OpenFont(FONT, 65)))
    return (err_sdl(TTF_GetError()));
  pos[0].y = pos[1].y = 30;
  while (++i < NB_DIR)
    {
      if (render_text(&aff, i, exe, selected) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      pos[0].x = WIDTH / 2 - (aff.text[0][i]->w + aff.text[1][i]->w) / 2;
      pos[1].x = pos[0].x + aff.text[0][i]->w + 50;
      if (SDL_BlitSurface(aff.text[0][i], NULL, exe->screen, &pos[0]) == SYS_ERR
          || SDL_BlitSurface(aff.text[1][i], NULL, exe->screen, &pos[1]) == SYS_ERR)
	return (err_sdl(SDL_GetError()));
      pos[0].y += HEIGHT / (NB_DIR + 1);
      pos[1].y += HEIGHT / (NB_DIR + 1);
    }
  free_controls(&aff);
  return (EXIT_SUCCESS);
}

static void	modif_controls(t_exe *exe, const int selected)
{
  SDL_Event 	tmp;
  int 		existant_keys = -1;
  int 		already_exist = 0;
  int 		stop = 0;

  if (exe->param.input[PAUSE] == 1)
    {
      exe->param.other_input = 1;
      while (!stop)
	{
	  SDL_WaitEvent(&tmp);
	  if (tmp.type == SDL_KEYDOWN)
	    {
	      while (++existant_keys < NB_DIR)
		if (tmp.key.keysym.sym ==
		    exe->param.controls[existant_keys].key.keysym.sym)
		  already_exist = 1;
	      if (!already_exist)
		exe->param.controls[selected].key.keysym.sym =
		  tmp.key.keysym.sym;
	      stop = 1;
	      exe->param.other_input = 0;
	      exe->param.input[PAUSE] = 0;
	    }
	}
    }
}

int		launch_controls(t_exe *exe)
{
  static int 	i;

  init_active(exe, CONTROLS);
  find_i(exe, &i, NB_DIR);
  modif_controls(exe, i);
  if (aff_controls_panel(exe, i) == EXIT_FAILURE
      || aff_help(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
