#include <string.h>
#include "menu.h"
#include "parameters.h"

static int	aff_help(t_exe *exe)
{
  int		h;
  TTF_Font	*font;
  SDL_Texture	*help[NB_MSG_CONTROLS];
  SDL_Color	white = {255, 255, 255, 0};
  SDL_Rect	pos;
  const char	*msg[NB_MSG_CONTROLS] =
  {CONTROLS_HELP, CONTROLS_ASSIGN, CONTROLS_WARNING};

  if (!(font = TTF_OpenFont(FONT, 30)))
    return (err_sdl(TTF_GetError()));
  pos.y = HEIGHT - 150;
  pos.h = 30;
  for (h = 0; h < NB_MSG_CONTROLS; h++)
    {
      exe->tmp = TTF_RenderText_Solid(font, msg[h], white);
      pos.x = WIDTH / 2 - exe->tmp->w / 2;
      pos.w = exe->tmp->w;
      if (!(help[h] = SDL_CreateTextureFromSurface(exe->renderer, exe->tmp))
	  || SDL_RenderCopy(exe->renderer, help[h], NULL, &pos) < 0)
	return (err_sdl(SDL_GetError()));
      SDL_FreeSurface(exe->tmp);
      pos.y += 50;
    }
  return (EXIT_SUCCESS);
}

static char	*get_key(t_exe *exe, const int i)
{
  const char	*key_tmp;
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
      aff->s_text[0][i] = TTF_RenderText_Solid(aff->font, options[i], white);
      aff->s_text[1][i] = TTF_RenderText_Solid(aff->font, key, white);
    }
  else
    {
      aff->s_text[0][i] = TTF_RenderText_Solid(aff->font, options[i], red);
      aff->s_text[1][i] = TTF_RenderText_Solid(aff->font, key, red);
    }
  free(key);
  if (!aff->s_text[0][i] || !aff->s_text[1][i])
    return (err_sdl(TTF_GetError()));
  return (EXIT_SUCCESS);
}

static int		aff_controls_panel(t_exe *exe, const int selected)
{
  int			i = -1;
  SDL_Rect		pos[2];
  t_aff_controls	aff;

  if (!(aff.font = TTF_OpenFont(FONT, 65)))
    return (err_sdl(TTF_GetError()));
  pos[0].y = pos[1].y = 30;
  pos[0].h = pos[1].h = 65;
  while (++i < NB_DIR)
    {
      if (render_text(&aff, i, exe, selected) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      pos[0].x = WIDTH / 2 - (aff.s_text[0][i]->w + aff.s_text[1][i]->w) / 2;
      pos[1].x = pos[0].x + aff.s_text[0][i]->w + 50;
      pos[0].w = aff.s_text[0][i]->w;
      pos[1].w = aff.s_text[1][i]->w;

      if (!(aff.t_text[0][i] = SDL_CreateTextureFromSurface(exe->renderer,
	    aff.s_text[0][i]))
	  || !(aff.t_text[1][i] = SDL_CreateTextureFromSurface(exe->renderer,
	    aff.s_text[1][i]))
	  || SDL_RenderCopy(exe->renderer, aff.t_text[0][i], NULL, &pos[0]) < 0
	  || SDL_RenderCopy(exe->renderer, aff.t_text[1][i], NULL, &pos[1]) < 0)
	return (err_sdl(SDL_GetError()));
      pos[0].y += HEIGHT / (NB_DIR + 1);
      pos[1].y += HEIGHT / (NB_DIR + 1);
    }
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
