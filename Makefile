CC		=	gcc
RM		=	rm -rf
NAME		=	pacman
CFLAGS		=	-O3 -W -Wall -Wextra			\
			-Iinclude
LDFLAGS		=	-lSDLmain -lSDL				\
			-lSDL_image				\
			-lSDL_mixer				\
			-lSDL_ttf
DFLAGS		=	-pg -g3

DIR_LIB		= 	lib/
DIR_SRC		=	src/
DIR_INIT	=	${DIR_SRC}init/
DIR_MENU	=	${DIR_SRC}menu/
DIR_GAME	=	${DIR_SRC}game/
DIR_CHASE	=	${DIR_GAME}ghosts/the_chase/
DIR_OPTIONS	=	${DIR_SRC}options/

SRCS		=	${DIR_SRC}main.c			\
			${DIR_SRC}tabs.c			\
			${DIR_SRC}background.c			\
			${DIR_SRC}input.c			\
			${DIR_SRC}tools.c			\
			${DIR_SRC}free.c

INIT		=	${DIR_INIT}init.c			\
			${DIR_INIT}init_game.c			\
			${DIR_INIT}create_map.c			\
			${DIR_INIT}init_goms.c			\
			${DIR_INIT}create_accur_map.c		\

MENU		=	${DIR_MENU}menu.c			\
			${DIR_MENU}menu_options.c

GAME		=	${DIR_GAME}launch_game.c		\
			${DIR_GAME}pacman.c			\
			${DIR_GAME}goms.c			\
			${DIR_GAME}scoring.c			\
			${DIR_GAME}aff_game.c			\
			${DIR_GAME}collision.c			\
			${DIR_CHASE}controller.c		\
			${DIR_CHASE}init.c			\
			${DIR_CHASE}model.c			\
			${DIR_CHASE}the_chase_v2.c		\
			${DIR_GAME}ghosts/ghosts.c		\
			${DIR_GAME}ghosts/position.c		\
			${DIR_GAME}ghosts/target.c		\
			${DIR_GAME}ghosts/blinky.c		\
			${DIR_GAME}ghosts/inky.c		\
			${DIR_GAME}ghosts/pinky.c		\
			${DIR_GAME}ghosts/clyde.c

OPTIONS		=	${DIR_OPTIONS}launch_controls.c		\
			${DIR_OPTIONS}launch_scores.c		\
			${DIR_OPTIONS}launch_credits.c		\
			${DIR_OPTIONS}high_scores.c		\
			${DIR_OPTIONS}launch_game_over.c	\
			${DIR_OPTIONS}fill_text.c

OBJS		=	$(SRCS:.c=.o) $(MENU:.c=.o)		\
			$(GAME:.c=.o) $(OPTIONS:.c=.o)		\
			$(INIT:.c=.o) $(LIB:.c=.o)

DYNLIBS		= 	-L./${DIR_LIB} -lgnl -llogger		\

all		:	$(NAME)

dev		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(CFLAGS) $(DFLAGS) $(DYNLIBS)
			make clean


${NAME}		:	$(OBJS)
			@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(CFLAGS) $(DYNLIBS)

clean		:
			@$(RM) $(OBJS)

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
