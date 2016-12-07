#include "menu.h"

/*
** Save pressed key in memory.
*/

static void	flush_key(t_exe *exe, const int pressed)
{
  int		key;

  if (exe->active[GAME_IDX])
    {
      for (key = 0; key < NB_INPUT; key++)
	if (exe->param.e_input.key.keysym.sym ==
	    exe->param.controls[key].key.keysym.sym)
	  exe->param.input[key] = pressed;
    }
  else
    switch (exe->param.e_input.key.keysym.sym)
      {
      case SDLK_RETURN:
	exe->param.input[PAUSE] = pressed;
	break;
      case SDLK_UP:
	exe->param.input[UP] = pressed;
	break;
      case SDLK_DOWN:
	exe->param.input[DOWN] = pressed;
	break;
      case SDLK_LEFT:
	exe->param.input[LEFT] = pressed;
	break;
      case SDLK_RIGHT:
	exe->param.input[RIGHT] = pressed;
	break;
      default:
	break;
      }
}

/*
** Know which key is pressed.
*/

int	get_input(t_exe *exe)
{
  if (!exe->param.other_input)
    while (SDL_PollEvent(&exe->param.e_input))
      {
	if (exe->param.e_input.type == SDL_QUIT)
	  {
	    exe->exit = 1;
	    break;
	  }
	if (exe->param.e_input.type == SDL_KEYDOWN)
	  {
	    if (exe->param.e_input.key.keysym.sym == SDLK_ESCAPE
		&& escape(exe) == EXIT_FAILURE)
	      return (EXIT_FAILURE);
	    flush_key(exe, 1);
	  }
	else if (exe->param.e_input.type == SDL_KEYUP)
	  flush_key(exe, 0);
      }
  return (EXIT_SUCCESS);
}
