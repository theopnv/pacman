#ifndef				THE_CHASE_H_
# define			THE_CHASE_H_

# include			<SDL2/SDL.h>

/* Parametrable macros */
# define SAFE_CELL  		('a')
# define C_WIDTH		(27)
# define C_HEIGHT		(27)

/* Do not touch beyond this point */
# define NDIR			(4)
# define STACK_SIZE		(C_WIDTH * C_HEIGHT)

/***********************************\
*              TYPEDEFS             *
\***********************************/

# ifndef T_COOR
#  define T_COOR

typedef struct		s_coordinate
{
  int			y;
  int			x;
}			t_coor;

# endif

typedef struct		s_cell
{
  int			F;
  int			G;
  int			H;
  t_coor   		cell;
  struct s_cell		*parent;
}			t_cell;

typedef struct		s_array
{
  int			idx;
  t_cell		*array[STACK_SIZE];
}			t_array;

typedef struct		s_the_chase
{
  int			last_out;
  char			**map;
  t_array		in;
  t_array		out;
}			t_the_chase;

typedef struct		s_external_elements
{
  t_coor		pos;
  t_coor		target;
  char			**map;
}			t_ext;

void			add_in(t_the_chase *, const t_ext *ext);
int			update_arrays(t_the_chase *, const int);
int			end_condition(const t_the_chase *, const t_coor);
int			calc_lower(const t_the_chase *);
t_coor			*flush_path(t_the_chase *);
t_the_chase		*init_the_chase(const t_ext *ext);
t_ext			*init_external_elem(const t_coor pos,
					    const t_coor target, char **map);

#endif			/* !THE_CHASE_H_ */
