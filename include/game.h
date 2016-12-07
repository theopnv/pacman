#ifndef				GAME_H_
# define			GAME_H_

# include			"main.h"

/************************************\
*            CHARACTERS              *
\************************************/

# define NB_PAC_SPRITES		(5)
# define SPEED			(3)
# define NB_GH			(4)
# define NB_CH			(5)


/************************************\
*                 MAP                *
\************************************/

# define START_ABS		(13)
# define START_ORD		(17)
# define M_HEIGHT		(31)
# define M_WIDTH		(28)
# define M_SIZE			(M_HEIGHT * M_WIDTH)
# define NB_TILES		(16)
# define TILE			(27)
# define SQ_TILE		(TILE * TILE)
# define MARGE_X		(30)
# define MARGE_Y		(30)
# define BORDER			(-1)

typedef int			(*t_moves)(t_exe *);
typedef int			(*t_dir_func)(const int);

/************************************\
*              FUNCTIONS             *
\************************************/

void				find_in_map(int *, int *);
void				adjust_accur_pos(t_exe *, const int);
void				update_pos(t_exe *, const int);
void				flush_accur_path(t_exe *, const int, const int);
int				aff_map(t_exe *);
int				aff_character(t_exe *, const int);
int				process_ghost(t_exe *, const int);
int				pacman(t_exe *);
int				ghosts(t_exe *);
int				blinky(t_exe *);
int				inky(t_exe *);
int				pinky(t_exe *exe);
int				clyde(t_exe *exe);
int				goms(t_exe *);
int				collision(t_exe *);
int				scoring(t_exe *);
int				init_accur_path(t_exe *, const int, int *);
t_coor				*algo_the_chase(const t_coor, const t_coor, char **);
t_coor   			random_path(t_exe *, const int/*, const double*/);
t_coor   			adjust_target(t_exe *, const int);
t_coor   			find_valid_near(t_exe *, t_coor, const int id);

#endif				/* GAME_H_ */
