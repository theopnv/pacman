#include "game.h"

static int    calc_dir(t_exe *exe, const int id, int i)
{
  t_coor      _0;
  t_coor      _1;

  _0.y = exe->game.ch[id].path[i].y;
  _0.x = exe->game.ch[id].path[i].x;
  _1.y = exe->game.ch[id].path[i + 1].y;
  _1.x = exe->game.ch[id].path[i + 1].x;

  if (_0.x == _1.x)    /* Vertical move */
    {
      if (_0.y - _1.y > 0)
          return (UP);
      else
          return (DOWN);
    }
  if (_0.y == _1.y)    /* Horizontal move */
    {
      if (_0.x - _1.x > 0)
          return (LEFT);
      else
          return (RIGHT);
    }
  return (PAUSE);
}

void      flush_accur_path(t_exe *exe, const int id, const int size)
{
  int i = 0, a_i = 0, d_i;
  int tile;
  int dir;

  for (i = 0; i < size && exe->game.ch[id].path[i].y != -1; i++)
    {
      tile = 0;
      dir = calc_dir(exe, id, i);

      while (tile < TILE && dir != PAUSE)
        {
          switch (dir)
            {
              case LEFT:
              {
                exe->game.ch[id].accur_path[a_i].y =
                  exe->game.ch[id].path[i].y * TILE;
                exe->game.ch[id].accur_path[a_i].x =
                  (exe->game.ch[id].path[i].x) * TILE - tile;
                break;
              }
              case UP:
              {
                exe->game.ch[id].accur_path[a_i].y =
                  (exe->game.ch[id].path[i].y) * TILE - tile;
                exe->game.ch[id].accur_path[a_i].x =
                  exe->game.ch[id].path[i].x * TILE;
                break;
              }
              case RIGHT:
              {
                exe->game.ch[id].accur_path[a_i].y =
                  exe->game.ch[id].path[i].y * TILE;
                exe->game.ch[id].accur_path[a_i].x =
                  exe->game.ch[id].path[i].x * TILE + tile;
                break;
              }
              case DOWN:
              {
                exe->game.ch[id].accur_path[a_i].y =
                  exe->game.ch[id].path[i].y * TILE + tile;
                exe->game.ch[id].accur_path[a_i].x =
                  exe->game.ch[id].path[i].x * TILE;
                break;
              }
            }
          ++a_i;
          ++tile;
        }
    }
    d_i = a_i;
    for (tile = 0; tile < TILE; tile++)
      {
        exe->game.ch[id].accur_path[d_i].y = exe->game.ch[id].accur_path[a_i - 1].y;
        exe->game.ch[id].accur_path[d_i].x = exe->game.ch[id].accur_path[a_i - 1].x;
        --a_i;
        ++d_i;
      }
}

static int    count_changing_dirs(t_coor *array, int *size)
{
  char        var;
  int         i;
  int         dirs = 0;

  if (array[0].x == array[1].x)
    var = 'x';
  if (array[0].y == array[1].y)
    var = 'y';
  for (i = 1; array[i].y != -1; i++)
    {
      if (var == 'x' && array[i].x != array[i - 1].x)
	{
	  var = 'y';
	  ++dirs;
	}
      if (var == 'y' && array[i].y != array[i - 1].y)
	{
	  var = 'x';
	  ++dirs;
	}
      ++(*size);
    }
  (*size) += 1;
  return (dirs);
}

int	init_accur_path(t_exe *exe, const int id, int *size)
{
  int	dirs;
  int	length;

  dirs = count_changing_dirs(exe->game.ch[id].path, size);
  length = (*size + dirs) * TILE + 1;
  if (exe->game.ch[id].accur_path)
    free(exe->game.ch[id].accur_path);
  if (!(exe->game.ch[id].accur_path =	malloc(sizeof(t_coor) * length)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void	update_pos(t_exe *exe, const int id)
{
  int	i;

  i = exe->game.ch[id].accur_idx;
  exe->game.ch[id].accur_pos.y = exe->game.ch[id].accur_path[i].y;
  exe->game.ch[id].accur_pos.x = exe->game.ch[id].accur_path[i].x;
  exe->game.ch[id].old_pos = exe->game.ch[id].pos;
  exe->game.ch[id].pos.y = exe->game.ch[id].accur_pos.y / TILE;
  exe->game.ch[id].pos.x = exe->game.ch[id].accur_pos.x / TILE;
  exe->game.ch[id].accur_idx += SPEED;
}
