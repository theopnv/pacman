#include "menu.h"
#include "parameters.h"

static int	aff(t_exe *exe, t_menu *menu)
{
  int		i = -1;
  const char	*options[NB_MENU_OPT] = {"START", "CONTROLS", "SCORES", "CREDITS"};
  SDL_Color	white = {255, 255, 255, 0};
  SDL_Color	red = {255, 0, 0, 0};
  SDL_Rect	pos;

  if (!(menu->font = TTF_OpenFont(FONT, 65)))
    return (err_sdl(TTF_GetError()));
  pos.y = Y_LOGO + 130;
  while (++i < SELECTABLE)
    {
      if (menu->selected != i)
	{
	  menu->text[i] = TTF_RenderText_Solid(menu->font, options[i], white);
	  if (!menu->text[i])
	    return (err_sdl(TTF_GetError()));
	}
      else
	{
	  menu->text[i] = TTF_RenderText_Solid(menu->font, options[i], red);
	  if (!menu->text[i])
	    return (err_sdl(TTF_GetError()));
	}
      pos.x = (WIDTH / 2) - (menu->text[i]->w / 2);
      pos.y += Y_OPTION;
      if (SDL_BlitSurface(menu->text[i], NULL, exe->screen, &pos) == SYS_ERR)
	return (err_sdl(SDL_GetError()));
    }
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
