#include "game.h"
#include "menu.h"
#include "parameters.h"

static int	print_game_over(t_exe *exe)
{
  SDL_Texture	*text;
  SDL_Color	red = {255, 0, 0, 0};
  SDL_Rect	pos;
  TTF_Font	*font;

  if (!(font = TTF_OpenFont(FONT, 100)))
    return (err_sdl(TTF_GetError()));
  exe->tmp = TTF_RenderText_Solid(font, MSG_GAME_OVER, red);
  pos.x = WIDTH / 2 - exe->tmp->w / 2;
  pos.y = HEIGHT / 2 - exe->tmp->h / 2;
  pos.h = 100;
  pos.w = exe->tmp->w;
  if (!(text = SDL_CreateTextureFromSurface(exe->renderer, exe->tmp))
      || SDL_RenderCopy(exe->renderer, text, NULL, &pos) < 0)
    return (err_sdl(SDL_GetError()));
  TTF_CloseFont(font);
  SDL_FreeSurface(exe->tmp);
  SDL_DestroyTexture(text);
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
