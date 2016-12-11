#include "game.h"
#include "menu.h"
#include "parameters.h"

static int	print_game_over(t_exe *exe)
{
  SDL_Surface	*text;
  SDL_Color	red = {255, 0, 0, 0};
  SDL_Rect	pos;
  TTF_Font	*font;

  if (!(font = TTF_OpenFont(FONT, 100)))
    return (err_sdl(TTF_GetError()));
  text = TTF_RenderText_Solid(font, MSG_GAME_OVER, red);
  pos.x = WIDTH / 2 - text->w / 2;
  pos.y = HEIGHT / 2 - text->h / 2;
  if (SDL_BlitSurface(text, NULL, exe->screen, &pos) == SYS_ERR)
    return (EXIT_FAILURE);
  TTF_CloseFont(font);
  SDL_FreeSurface(text);
    return (EXIT_SUCCESS);
}

int	launch_game_over(t_exe *exe)
{
  if (change_music(exe, PAC_TRAP) == EXIT_FAILURE
      || print_game_over(exe) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (get_high_scores(exe) == EXIT_FAILURE
      || is_in_h_scores(exe) == EXIT_SUCCESS)
    {
      init_active(exe, HIGH_SCORE);
      init_game(exe, NOREINIT);
    }
  else
    init_game(exe, REINIT);
  return (EXIT_SUCCESS);
}
