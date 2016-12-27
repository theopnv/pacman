#ifndef				MENU_H_
# define			MENU_H_

# include			"main.h"

# define LOGO_WIDTH		(830)
# define LOGO_HEIGHT		(192)
# define Y_LOGO			(50)
# define Y_OPTION		(120)
# define NB_MENU_OPT		(8)
# define SELECTABLE		(4)

typedef enum			s_menu_opt
  {
    GAME,
    CONTROLS,
    SCORES,
    CREDITS,
    MENU,
    STARTUP,
    HIGH_SCORE,
    GAME_OVER
  }				t_menu_opt;

typedef struct		s_menu
{
  int			selected;
  TTF_Font		*font;
  SDL_Texture		*logo;
  SDL_Texture		*text[SELECTABLE]; /* Only selectable options are visible */
}			t_menu;

int			menu_options(t_exe *, t_menu *);

#endif			/* !MENU_H_ */
