#include <stdlib.h>
#include "menu.h"
#include "parameters.h"

static int	aff_logo(t_exe *exe, t_menu *menu)
{
  SDL_Rect	pos;

  pos.x = (WIDTH / 2) - (LOGO_WIDTH / 2);
  pos.y = Y_LOGO;
  pos.w = LOGO_WIDTH;
  pos.h = LOGO_HEIGHT;
  if (!(exe->tmp = IMG_Load(IMG_LOGO))
      || !(menu->logo = SDL_CreateTextureFromSurface(exe->renderer, exe->tmp))
      || SDL_RenderCopy(exe->renderer, menu->logo, NULL, &pos) < 0)
    return (err_sdl(SDL_GetError()));
  SDL_FreeSurface(exe->tmp);
  SDL_DestroyTexture(menu->logo);
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
  return (EXIT_SUCCESS);
}
