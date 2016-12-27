#include "menu.h"
#include "parameters.h"

static int	aff(t_exe *exe, t_menu *menu)
{
  int		i = -1;
  const char	*options[NB_MENU_OPT] = {"START", "CONTROLS", "SCORES", "CREDITS"};
  SDL_Color	white = {255, 255, 255, 0};
  SDL_Color	red = {255, 0, 0, 0};
  SDL_Rect	pos;
  SDL_Surface	*stext[SELECTABLE];

  if (!(menu->font = TTF_OpenFont(FONT, 65)))
    return (err_sdl(TTF_GetError()));
  pos.y = Y_LOGO + 130;
  pos.h = 65;
  while (++i < SELECTABLE)
    {
      if (menu->selected != i)
	{
	  if (!(stext[i] = TTF_RenderText_Solid(menu->font, options[i], white)))
	    return (err_sdl(TTF_GetError()));
	}
      else
	{
	  if (!(stext[i] = TTF_RenderText_Solid(menu->font, options[i], red)))
	    return (err_sdl(TTF_GetError()));
	}
      pos.x = (WIDTH / 2) - (stext[i]->w / 2);
      pos.y += Y_OPTION;
      pos.w = stext[i]->w;
      if (!(menu->text[i] = SDL_CreateTextureFromSurface(exe->renderer, stext[i]))
	  || SDL_RenderCopy(exe->renderer, menu->text[i], NULL, &pos) < 0)
	return (err_sdl(SDL_GetError()));
      SDL_FreeSurface(stext[i]);
      SDL_DestroyTexture(menu->text[i]);
    }
  TTF_CloseFont(menu->font);
  return (EXIT_SUCCESS);
}

int		menu_options(t_exe *exe, t_menu *menu)
{
  static int	i = 0;

  find_i(exe, &i, SELECTABLE);
  menu->selected = i;
  if (aff(exe, menu) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
