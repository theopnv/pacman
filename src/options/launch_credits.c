#include "parameters.h"
#include "main.h"

static int	init_bltxt(t_bltxt *bltxt, char *text, const int y)
{
  TTF_Font	*font;
  SDL_Color	white = {255, 255, 255, 0};

  if (!(font = TTF_OpenFont(FONT, 40)))
    return (err_sdl(TTF_GetError()));
  bltxt->surface = TTF_RenderText_Solid(font, text, white);
  bltxt->text = text;
  bltxt->pos.y = y;
  bltxt->pos.x = WIDTH / 2 - bltxt->surface->w / 2;
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
      if (SDL_BlitSurface(bltxt[i].surface, NULL, exe->screen, &bltxt[i].pos)
          == SYS_ERR)
        return (err_sdl(SDL_GetError()));
      SDL_FreeSurface(bltxt[i].surface);
    }
  free(bltxt);
  return (EXIT_SUCCESS);
}
