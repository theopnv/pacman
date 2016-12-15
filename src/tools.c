#include <stdio.h>
#include <errno.h>
#include "menu.h"
#include "game.h"
#include "parameters.h"

int	err_c(const int errnum)
{
  fprintf(stderr, "%s\n", strerror(errnum));
  return (EXIT_FAILURE);
}

int	err_sdl(const char *error)
{
  fprintf(stderr, "Erreur : %s\n", error);
  return (EXIT_FAILURE);
}

int	escape(t_exe *exe)
{
  if (Mix_Playing(0))
    Mix_HaltChannel(0);
  if (exe->active[MENU] == 1)
     exe->exit = 1;
  else
    {
      if (exe->active[GAME] == 1 || exe->active[STARTUP])
	{
	  init_game(exe, REINIT);
	  if (change_music(exe, PAC_TRAP) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	}
      init_active(exe, MENU);
    }
  return (EXIT_SUCCESS);
}

int	change_music(t_exe *exe, char *path)
{
  if (!(exe->music = Mix_LoadMUS(path))
      || Mix_PlayMusic(exe->music, -1) == SYS_ERR)
    return (err_sdl(Mix_GetError()));
  Mix_VolumeMusic(MIX_MAX_VOLUME);
  return (EXIT_SUCCESS);
}

void	find_i(t_exe *exe, int *i, int nb_lines)
{
  if (exe->param.input[DOWN] == 1)
    ++(*i);
  if (exe->param.input[UP] == 1)
    --(*i);
  if (*i == nb_lines)
    *i = 0;
  if (*i == -1)
    *i = nb_lines - 1;
}
