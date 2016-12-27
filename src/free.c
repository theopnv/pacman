#include "game.h"

/*
** Frees at program's stopping.
*/

static void	free_map(t_exe *exe)
{
 int		i;

  for (i = 0; i < M_HEIGHT; i++)
    {
      free(exe->game.map.map[i]);
      free(exe->game.map.goms[i]);
    }
  free(exe->game.map.map);
  free(exe->game.map.goms);
  for (i = 0; i < M_HEIGHT * TILE; i++)
    free(exe->game.map.accur_map[i]);
  free(exe->game.map.accur_map);
  free(exe->game.s_map);
}

static void	free_player(t_exe *exe)
{
  free(exe->player.pseudo);
}

static void	free_ch(t_exe *exe, const int id)
{
  SDL_FreeSurface(exe->game.ch[id].sprite);
  if (exe->game.ch[id].accur_path)
    free(exe->game.ch[id].accur_path);
}

void	free_end(t_exe *exe)
{
  int   id;

  free_player(exe);
  free_high_scores(exe);
  free_map(exe);
  SDL_FreeSurface(exe->game.maze_sprite);
  for (id = 0; id < NB_CH; id++)
    free_ch(exe, id);
}
