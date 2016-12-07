#include "game.h"

int	in_map(const int y, const int x)
{
  if (y < 1 || y > M_HEIGHT - 2
      || x < 1 || x > M_WIDTH - 2)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

void	find_in_map(int *y, int *x)
{
  if (*y < 1)
    *y = 1;
  if (*y > M_HEIGHT - 2)
    *y = M_HEIGHT - 2;
  if (*x < 1)
    *x = 1;
  if (*x > M_WIDTH - 2)
    *x = M_WIDTH - 2;
}

t_coor		find_valid_near(t_exe *exe, t_coor pos, const int id)
{
  t_coor	max;
  t_coor	target;

  max.y = pos.y + 4;
  max.x = pos.x + 4;
  target = pos;
  for (pos.y = pos.y - 3; pos.y < max.y; pos.y++)
    {
      for (pos.x = pos.x - 3; pos.x < max.x; pos.x++)
	{
	  if (in_map(pos.y, pos.x) == EXIT_SUCCESS
	      && exe->game.map.map[pos.y][pos.x] == 'a'
	      && pos.y != exe->game.ch[id].pos.y
	      && pos.x != exe->game.ch[id].pos.x)
	    return (pos);
	}
    }
  return (target);
}

static t_coor dont_target_pos(t_coor pos, t_exe *exe)
{
  switch (exe->game.ch[PAC].state)
    {
      case LEFT:
	{
	  --pos.x;
	  return (pos);
	}
      case UP:
	{
	  --pos.y;
	  return (pos);
	}
      case RIGHT:
	{
	  ++pos.x;
	  return (pos);
	}
      case DOWN:
	{
	  ++pos.y;
	  return (pos);
	}
      default:
	return (pos);
    }
}

t_coor		adjust_target(t_exe *exe, const int id)
{
  t_coor	pos;

  pos = exe->game.ch[id].target;
  if (pos.y == exe->game.ch[id].pos.y && pos.x == exe->game.ch[id].pos.x)
    pos = dont_target_pos(pos, exe);
  if (in_map(pos.y, pos.x) == EXIT_FAILURE
      || exe->game.map.map[pos.y][pos.x] != 'a')
    {
      find_in_map(&pos.y, &pos.x);
      if (exe->game.map.map[pos.y][pos.x] == 'a'
	  && pos.y != exe->game.ch[PAC].pos.y && pos.x != exe->game.ch[PAC].pos.x)
    	return (pos);
      return (find_valid_near(exe, pos, id));
    }
  return (pos);
}
