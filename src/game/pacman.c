#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "the_chase.h"

static void	update_pac_pos(t_exe *exe)
{
  exe->game.ch[PAC].pos.x = (exe->game.ch[PAC].accur_pos.x + (TILE / 2)) / TILE;
  exe->game.ch[PAC].pos.y = (exe->game.ch[PAC].accur_pos.y + (TILE / 2)) / TILE;
}

static int	is_wall(t_exe *exe, const int dir)
{
  int		x, y;

  y = exe->game.ch[PAC].accur_pos.y;
  x = exe->game.ch[PAC].accur_pos.x;
  switch (dir)
    {
      case LEFT:
      	if (exe->game.map.accur_map[y][x - 1] == 'a'
	    && exe->game.map.accur_map[y + TILE - 1][x - 1] == 'a')
	  return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
      case UP:
      	if (exe->game.map.accur_map[y - 1][x + 1] == 'a'
	    && exe->game.map.accur_map[y - 1][x + TILE - 1] == 'a')
	  return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
      case RIGHT:
      	if (exe->game.map.accur_map[y][x + TILE] == 'a'
	    && exe->game.map.accur_map[y + TILE - 1][x + TILE] == 'a')
	  return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
      case DOWN:
	if (exe->game.map.accur_map[y + TILE][x + 1] == 'a'
	    && exe->game.map.accur_map[y + TILE][x + TILE - 1] == 'a')
	  return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

static int	left(t_exe *exe)
{
  exe->game.ch[PAC].state = LEFT;
  exe->game.ch[PAC].accur_pos.x -= SPEED;
  return (EXIT_SUCCESS);
}

static int	up(t_exe *exe)
{
  exe->game.ch[PAC].state = UP;
  exe->game.ch[PAC].accur_pos.y -= SPEED;
  return (EXIT_SUCCESS);
}

static int	right(t_exe *exe)
{
  exe->game.ch[PAC].state = RIGHT;
  exe->game.ch[PAC].accur_pos.x += SPEED;
  return (EXIT_SUCCESS);
}

static int	down(t_exe *exe)
{
  exe->game.ch[PAC].state = DOWN;
  exe->game.ch[PAC].accur_pos.y += SPEED;
  return (EXIT_SUCCESS);
}

int	pacman(t_exe *exe)
{
  int	tmp_dir = -1;

  const t_moves	moves[NB_DIR] =
    {left, up, right, down};

  exe->game.ch[PAC].state = PAUSE;
  exe->param.input[PAUSE] = 0;
  /* Calculation of input direction */
  while (++tmp_dir < NB_DIR)
    if (exe->param.input[tmp_dir] == 1)
      {
	if (exe->game.ch[PAC].dir == -1)
	  exe->game.ch[PAC].dir = tmp_dir;
	else
	  exe->game.ch[PAC].next_dir = tmp_dir;
      }
  if (exe->game.ch[PAC].dir != -1) /* Some input is entered */
    {
      if (is_wall(exe, exe->game.ch[PAC].dir) == EXIT_FAILURE)
	moves[exe->game.ch[PAC].dir](exe);
      if (exe->game.ch[PAC].next_dir != -1)
	if (is_wall(exe, exe->game.ch[PAC].next_dir) == EXIT_FAILURE)
	  exe->game.ch[PAC].dir = exe->game.ch[PAC].next_dir;
    }
  update_pac_pos(exe);
  aff_character(exe, PAC);
  return (EXIT_SUCCESS);
}
