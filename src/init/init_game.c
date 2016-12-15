#include <SDL/SDL_image.h>
#include <errno.h>
#include "game.h"
#include "parameters.h"

void	init_score(t_exe *exe)
{
  int	 i;

  for (i = 0; i < NB_HIGH_SCORES; i++)
  {
    exe->game.score.high_scores[i].pseudo = NULL;
    exe->game.score.high_scores[i].score = NULL;
  }
  get_high_scores(exe);
  exe->game.score.lives = 2;
  exe->game.score.total_goms = 0;
  exe->game.score.catched_goms = 0;
  exe->game.score.lvl = 1;
  exe->game.score.score = 0;
}

void	init_events(t_exe *exe)
{
  /* Initialize events */
  exe->param.input[UP] = 0;
  exe->param.input[DOWN] = 0;
  exe->param.input[LEFT] = 0;
  exe->param.input[RIGHT] = 0;
  exe->param.input[PAUSE] = 0;
}

void	init_ch(t_exe *exe, const int id,
		const int abs, const int ord,
		const char *img_path)
{
  if (id == PAC)
    {
      exe->game.ch[PAC].dir = -1;
      exe->game.ch[PAC].next_dir = -1;
      exe->game.ch[PAC].state = PAUSE;
    }
  else
    {
      exe->game.ch[id].accur_path = NULL;
      exe->game.ch[id].prev_time = 0;
      exe->game.ch[id].state = UP;
    }
  exe->game.ch[id].accur_pos.x = abs * TILE;
  exe->game.ch[id].accur_pos.y = ord * TILE;
  exe->game.ch[id].pos.x = abs;
  exe->game.ch[id].pos.y = ord;
  exe->game.ch[id].sprite = IMG_Load(img_path);
}

void	init_game(t_exe *exe, const int dead)
{
  init_ch(exe, PAC, START_ABS, START_ORD, IMG_PAC);
  init_ch(exe, BLINKY, START_ABS, START_ORD - 6, IMG_BLINKY);
  init_ch(exe, INKY, START_ABS - 1, START_ORD - 3, IMG_INKY);
  init_ch(exe, PINKY, START_ABS, START_ORD - 3, IMG_PINKY);
  init_ch(exe, CLYDE, START_ABS + 1, START_ORD - 3, IMG_CLYDE);
  if (dead)
    {
      exe->game.startup = 0;
      init_score(exe);
      init_goms(exe);
    }
  init_events(exe);
}
