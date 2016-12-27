#include <errno.h>
#include "game.h"
#include "menu.h"
#include "parameters.h"

extern const t_char	g_assoc_map[NB_TILES];

static int	build_map(t_exe *exe)
{
  int		tab;
  int		y, x;
  SDL_Rect	srcrect, dstrect;

  if (!(exe->game.s_map = SDL_CreateRGBSurface(0, (M_WIDTH + 1)* TILE,
	  M_HEIGHT * TILE, 32, 0, 0, 0, 0)))
    return (EXIT_FAILURE);
  dstrect.y = 0;
  srcrect.y = 0;
  srcrect.w = TILE;
  srcrect.h = TILE;
  for (y = 0; y < M_HEIGHT; y++)
    {
      dstrect.x = MARGE_X;
      for (x = 0; x < M_WIDTH; x++)
	{
	  for (tab = 0; tab < NB_TILES; tab++)
	    if (exe->game.map.map[y][x] == g_assoc_map[tab].key)
	      {
		/* Fill blocks of >= 3x3 with blank tile */
		if (g_assoc_map[tab].key == 'p')
		  srcrect.x = 0;
		else
		  srcrect.x = g_assoc_map[tab].idx * TILE;
	      }
	  if (SDL_BlitSurface(exe->game.maze_sprite, &srcrect, exe->game.s_map, &dstrect) < 0)
	    return (err_sdl(SDL_GetError()));
	  dstrect.x += TILE;
	}
      dstrect.y += TILE;
    }
  return (EXIT_SUCCESS);
}

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
  exe->screen = SDL_CreateWindow(WIN_NAME,
  		   SDL_WINDOWPOS_CENTERED,
  		   SDL_WINDOWPOS_CENTERED,
  		   WIDTH, HEIGHT,
  		   SDL_WINDOW_OPENGL);
  exe->renderer = SDL_CreateRenderer(exe->screen, -1, 0);
  if (!exe->screen || !exe->renderer)
    return (err_sdl(SDL_GetError()));
  exe->param.other_input = 0;
  exe->param.k_repeat.hold = HOLD;
  exe->param.k_repeat.delay = DELAY;
  if (!(exe->game.maze_sprite = IMG_Load(IMG_MAZE)))
    return (err_sdl(SDL_GetError()));
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

  if (init_struct(exe) == EXIT_FAILURE
      || init_player(exe) == EXIT_FAILURE
      || create_map(exe) == EXIT_FAILURE
      || init_music(exe) == EXIT_FAILURE
      || build_map(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  init_game(exe, REINIT);
  init_controls(exe);
  return (EXIT_SUCCESS);
}
