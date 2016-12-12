#include <SDL/SDL_image.h>
#include <errno.h>
#include "game.h"
#include "menu.h"
#include "parameters.h"

void	init_active(t_exe *exe, const int active)
{
  int	menu_opt = -1;

  while (++menu_opt < NB_MENU_OPT)
    if (menu_opt != active)
      exe->active[menu_opt] = 0;
    else
      exe->active[active] = 1;
}

static void	init_controls(t_exe *exe)
{
  /* Default controls */
  exe->param.controls[UP].key.keysym.sym = SDLK_UP;
  exe->param.controls[DOWN].key.keysym.sym = SDLK_DOWN;
  exe->param.controls[LEFT].key.keysym.sym = SDLK_LEFT;
  exe->param.controls[RIGHT].key.keysym.sym = SDLK_RIGHT;
  exe->param.controls[PAUSE].key.keysym.sym = SDLK_SPACE;
  init_events(exe);
}

int 	init_player(t_exe *exe)
{
  int	i;

  if (!(exe->player.pseudo = calloc(PSEUDO_LENGTH, sizeof(char)))
      || !(exe->player.pseudo = memset(exe->player.pseudo, '_', PSEUDO_LENGTH - 1)))
    return (err_c(errno));
  /* Set default pseudo */
  for (i = 0; i < 3; ++i)
    exe->player.pseudo[i] = 'a';
  exe->player.i = 0;
  return (EXIT_SUCCESS);
}

static int	init_struct(t_exe *exe)
{
  exe->exit = 0;
  init_active(exe, MENU);
  if (!(exe->screen = SDL_SetVideoMode(WIDTH, HEIGHT, COLOR_BIT, SDL_HWSURFACE | SDL_DOUBLEBUF)))
    return (err_sdl(SDL_GetError()));
  exe->param.other_input = 0;
  exe->param.k_repeat.hold = HOLD;
  exe->param.k_repeat.delay = DELAY;
  exe->game.maze_sprite = IMG_Load(IMG_MAZE);
  return (EXIT_SUCCESS);
}

static int	init_music(t_exe *exe)
{
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == SYS_ERR)
    return (err_sdl(Mix_GetError()));
  if (change_music(exe, PAC_TRAP) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  Mix_AllocateChannels(1);
  Mix_Volume(0, MIX_MAX_VOLUME / 4);
  if (!(exe->waka = Mix_LoadWAV(WAKA)))
    return (err_sdl(Mix_GetError()));
  return (EXIT_SUCCESS);
}

int	init(t_exe *exe)
{
  if (SDL_Init(SDL_INIT_VIDEO) == SYS_ERR)
    return (err_sdl(SDL_GetError()));
  if (TTF_Init() == SYS_ERR)
    return (err_sdl(TTF_GetError()));

  SDL_WM_SetIcon(SDL_LoadBMP(IMG_ICON), NULL);
  SDL_WM_SetCaption(WIN_NAME, NULL);
  if (init_struct(exe) == EXIT_FAILURE
      || init_player(exe) == EXIT_FAILURE
      || create_map(exe) == EXIT_FAILURE
      || init_music(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  init_game(exe, REINIT);
  init_controls(exe);
  return (EXIT_SUCCESS);
}
