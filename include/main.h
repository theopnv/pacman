#ifndef				MAIN_H_
# define			MAIN_H_

# include			<SDL/SDL.h>
# include			<SDL/SDL_mixer.h>
# include			<SDL/SDL_ttf.h>


/************************************\
*            MAIN VARIABLES          *
\************************************/

# define SYS_ERR		(-1)
# define FRAME			(15)
# define NB_INPUT		(5)
# define WIDTH			(1200)
# define HEIGHT			(900)
# define COLOR_BIT		(32)
# define NB_HIGH_SCORES		(10)
# define HOLD			(2000)
# define DELAY			(2000)
# define MENU_FRAME		(100)
# define GAME_IDX		(0)
# define LOG_INFO		("INFO")

/*****				OPTIONS
*/
# define LEFT_MARGIN		(WIDTH / 6)
# define NB_DIR			(5)
# define NB_MSG_CONTROLS	(3)
# define PSD			(0)
# define SCR			(1)

/*****				SCORES
*/
# define NO_HS			(2)
# define HS_LINE_LENGTH		(8)
# define NOT_IN_HS		(11)
# define PSEUDO_LENGTH		(11)
# define SCORE_LENGTH		(10)
# define LINE_LENGTH		(PSEUDO_LENGTH + SCORE_LENGTH + 3)


/************************************\
*            MAIN STRUCTURES         *
\************************************/

typedef enum			e_dir
  {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    PAUSE
  }				t_dir;

typedef enum			e_id_ghost
  {
    PAC,
    BLINKY,
    INKY,
    PINKY,
    CLYDE
  }				t_id_ghost;

# ifndef T_COOR
#  define T_COOR

typedef struct		s_coordinate
{
  int			y;
  int			x;
}			t_coor;

# endif

typedef struct		s_blit_text
{
  char			*text;
  SDL_Rect		pos;
  SDL_Surface		*surface;
}			t_bltxt;

typedef struct		s_char
{
  char			key;
  int			idx;
}			t_char;

typedef struct		s_key_repeat
{
  int			hold;
  int			delay;
}			t_key_repeat;

typedef struct		s_param
{
  int			other_input;
  int			input[NB_INPUT];
  SDL_Event		controls[NB_INPUT];
  SDL_Event		e_input;
  t_key_repeat		k_repeat;
}			t_param;

typedef struct		s_high_scores
{
  char			*pseudo;
  char			*score;
}			t_hs;

typedef struct		s_score
{
  int			lives;
  int			total_goms;
  int			catched_goms;
  int			lvl;
  int			score;
  t_hs			high_scores[NB_HIGH_SCORES];
}			t_score;

typedef struct		s_map
{
  char			**map;
  char			**accur_map;
  char			**goms;
}			t_map;

typedef struct		s_character
{
  char			*name;
  int			state;
  t_coor   		pos;
  t_coor   		accur_pos;
  SDL_Surface		*sprite;
  /* For ghosts only */
  int			idx;
  int			accur_idx;
  int			prev_time;
  t_coor   		target;
  t_coor   		*path;
  t_coor   		*accur_path;
  t_coor   		old_pos;
  t_coor   		old_accur_pos;
  /* For pacman only */
  int			dir;
  int			next_dir;
}			t_character;

typedef struct		s_player
{
  char			*pseudo;
  int			i;
}			t_player;

typedef struct		s_game
{
  int			startup;
  int			startup_time;
  t_map			map;
  t_score		score;
  SDL_Surface		*maze_sprite;
  SDL_Surface		*s_map;
  t_character		ch[5];
}			t_game;

typedef struct		s_exe
{
  int			exit;
  int			active[8/*NB_MENU_OPT*/];
  SDL_Event		event;
  SDL_Surface		*screen;
  Mix_Music		*music;
  Mix_Chunk		*waka;
  t_player		player;
  t_param		param;
  t_game		game;
}			t_exe;

typedef int		(*t_options)(t_exe *);

/*****			CONTROLS STRUCTURE
*/
typedef struct		s_aff_controls
{
  TTF_Font		*font;
  SDL_Surface		*text[2][NB_DIR];
}			t_aff_controls;

/************************************\
*            MAIN FUNCTIONS          *
\************************************/

void			free_loop(t_exe *);
void			free_end(t_exe *);
void			free_high_scores(t_exe *);
void			find_i(t_exe *, int *, int);
void			init_events(t_exe *);
void			init_active(t_exe *, const int);
void			init_score(t_exe *);
void			init_game(t_exe *, const int);
void			init_ch(t_exe *, const int, const int,
				const int, const char *);
char			*get_next_line(const int);
char			*remove_underscores(char *);
int			escape(t_exe *);
int			get_input(t_exe *);
int			change_music(t_exe *, char *);
int			calc_center(const int);
int			get_score_to_delete(t_exe *, const int);
int			get_pseudo(t_exe *);
int			in_map(const int, const int);
int			calc_center(const int);
int			get_high_scores(t_exe *);
int			init_goms(t_exe *);
int			init_player(t_exe *exe);
int			create_accur_map(t_exe *);
int			aff_bg(const t_exe *);
int			init(t_exe *);
int			create_map(t_exe *);
int			err_c(const int);
int			err_sdl(const char *);
int			launch_startup(t_exe *);
int			launch_menu(t_exe *);
int			launch_game(t_exe *);
int			launch_controls(t_exe *);
int			launch_scores(t_exe *);
int			launch_high_score(t_exe *);
int			launch_credits(t_exe *);
int			launch_game_over(t_exe *);
int			is_in_h_scores(t_exe *);
int			logger(const char *format, ...);

#endif			/* ! MAIN_H_ */
