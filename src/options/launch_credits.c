#include "parameters.h"
#include "main.h"

static int	init_bltxt(t_bltxt *bltxt, const char *text, const int y)
{
  TTF_Font	*font;
  SDL_Color	white = {255, 255, 255, 0};

  if (!(font = TTF_OpenFont(FONT, 40)))
    return (err_sdl(TTF_GetError()));
  bltxt->surface = TTF_RenderText_Solid(font, text, white);
  bltxt->pos.y = y;
  bltxt->pos.x = WIDTH / 2 - bltxt->surface->w / 2;
  bltxt->pos.h = 40;
  bltxt->pos.w = bltxt->surface->w;
  TTF_CloseFont(font);
  return (EXIT_SUCCESS);
}

static t_bltxt	*init_bltxt_array()
{
  t_bltxt	*bltxt;

  if (!(bltxt = malloc(sizeof(t_bltxt) * 3)))
    return (NULL);
  if (init_bltxt(&bltxt[0], MADE_BY, HEIGHT / 4) == EXIT_FAILURE
      || init_bltxt(&bltxt[1], CREATED_IN, HEIGHT / 2) == EXIT_FAILURE
      || init_bltxt(&bltxt[2], ORIGINAL_GAME, HEIGHT / 4 * 3) == EXIT_FAILURE)
    return (NULL);
  return (bltxt);
}

int		launch_credits(t_exe *exe)
{
  int		i;
  t_bltxt	*bltxt;

  if (!(bltxt = init_bltxt_array()))
    return (EXIT_FAILURE);
  for (i = 0; i < 3; i++)
    {
      if (!(bltxt[i].texture = SDL_CreateTextureFromSurface(exe->renderer,
	    bltxt[i].surface))
	  || SDL_RenderCopy(exe->renderer, bltxt[i].texture, NULL, &bltxt[i].pos) < 0)
	return (err_sdl(SDL_GetError()));
      SDL_FreeSurface(bltxt[i].surface);
      SDL_DestroyTexture(bltxt[i].texture);
    }
  free(bltxt);
  return (EXIT_SUCCESS);
}
