#include "game.h"
#include "the_chase.h"

static int	is_at_crossway(t_exe *exe, const int id)
{
  int		i = 0;
  t_coor	pos;

  pos = exe->game.ch[id].pos;
  if (exe->game.map.map[pos.y][pos.x -1] == 'a')
    ++i;
  if (exe->game.map.map[pos.y - 1][pos.x] == 'a')
    ++i;
  if (exe->game.map.map[pos.y][pos.x + 1] == 'a')
    ++i;
  if (exe->game.map.map[pos.y + 1][pos.x] == 'a')
    ++i;
  if (i > 2)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

t_coor		random_path(t_exe *exe, const int id/*, const double rand_factor*/)
{
  t_coor	target;

  if (is_at_crossway(exe, id) == EXIT_SUCCESS)
    {
      target.y = rand() % M_HEIGHT;
      target.x = rand() % M_WIDTH;
      target = find_valid_near(exe, target, id);
      return (target);
    }
  return (exe->game.ch[id].target);
}

static int	new_pos(t_exe *exe, const int id)
{
  if (exe->game.ch[id].accur_idx > TILE)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}

int		the_chase(t_exe *exe, const int id)
{
  int		size = 0;
  t_coor	*path;

  exe->game.ch[id].old_accur_pos = exe->game.ch[id].accur_pos;
  if ((path = algo_the_chase(exe->game.ch[id].pos,
      exe->game.ch[id].target, exe->game.map.map)))
    exe->game.ch[id].path = path;
  if (!exe->game.ch[id].path || init_accur_path(exe, id, &size) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  flush_accur_path(exe, id, size);
  exe->game.ch[id].accur_idx = 0;
  exe->game.ch[id].prev_time = 1;
  free(path);
  return (EXIT_SUCCESS);
}

int	process_ghost(t_exe *exe, const int id)
{
  /* Adjust the target for inky, pinky, clyde */
  if (id != BLINKY)
    exe->game.ch[id].target = adjust_target(exe, id);
  if (exe->game.ch[id].prev_time == 0 || new_pos(exe, id) == EXIT_SUCCESS)
    if (the_chase(exe, id) == EXIT_FAILURE)
      return (EXIT_FAILURE);
  update_pos(exe, id);
  if (aff_character(exe, id) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int	ghosts(t_exe *exe)
{
  if (blinky(exe) == EXIT_FAILURE
      || inky(exe) == EXIT_FAILURE
      || pinky(exe) == EXIT_FAILURE
      || clyde(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
