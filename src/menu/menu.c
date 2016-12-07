#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "menu.h"
#include "parameters.h"

static void	free_menu(t_menu *menu)
{
  int		i = -1;

  while (++i < NB_MENU_OPT - 3)
    SDL_FreeSurface(menu->text[i]);
  SDL_FreeSurface(menu->logo);
  TTF_CloseFont(menu->font);
}

static int	aff_logo(t_exe *exe, t_menu *menu)
{
  SDL_Rect	pos;

  pos.x = (WIDTH / 2) - (LOGO_WIDTH / 2);
  pos.y = Y_LOGO;
  if (!(menu->logo = IMG_Load(IMG_LOGO))
      || SDL_BlitSurface(menu->logo, NULL, exe->screen, &pos) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  return (EXIT_SUCCESS);
}

int		launch_menu(t_exe *exe)
{
  t_menu	menu;

  if (aff_logo(exe, &menu) == EXIT_FAILURE
      || menu_options(exe, &menu) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (exe->param.input[PAUSE] == 1)
    {
      exe->active[menu.selected] = 1;
      if (exe->active[GAME] == 1 && change_music(exe, EIGHTIES_MIX) == EXIT_FAILURE)
      	return (EXIT_FAILURE);
      exe->active[MENU] = 0;
    }
  free_menu(&menu);
  return (EXIT_SUCCESS);
}
