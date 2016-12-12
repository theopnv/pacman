#ifndef				PARAMETERS_H_
# define			PARAMETERS_H_

/************************************\
*             ARGUMENTS              *
\************************************/

# define ARG_DEBUG		("--debug")
# define ARG_DEBUG_LENGTH	(7)

/************************************\
*               COLORS               *
\************************************/

# define WHITE			("\033[0m")
# define RED			("\033[1;31m")
# define GREEN			("\033[1;32m")
# define CYAN			("\033[1;36m")
# define BLUE			("\033[1;34m")
# define YELLOW			("\033[1;33m")


/************************************\
*               STRINGS              *
\************************************/

# define WIN_NAME		("Pacman")
# define LEVEL			("LEVEL")
# define SCORE			("SCORE")
# define LIVES			("LIVES")
# define CONTROLS_HELP		("To assign a new key, press enter")
# define CONTROLS_ASSIGN	("and choose a key.")
# define CONTROLS_WARNING	("A key cannot be assigned twice.")
# define MSG_GAME_OVER		("GAME OVER")
# define PROMPT_HS		("Enter your name")
# define MADE_BY		("Made by Theo Penavaire")
# define CREATED_IN		("Created in 2016")
# define ORIGINAL_GAME		("Original game by Toru Iwatani (1979)")
# define HS_LINE		("___;000\n")

/************************************\
*                PATHS               *
\************************************/

# define IMG_ICON		("ressources/img/ico.bmp")
# define IMG_LOGO		("ressources/img/logo.png")
# define IMG_PAC		("ressources/img/pacman_sprites.png")
# define IMG_BLINKY		("ressources/img/Blinky.png")
# define IMG_INKY		("ressources/img/Inky.png")
# define IMG_PINKY		("ressources/img/Pinky.png")
# define IMG_CLYDE		("ressources/img/Clyde.png")
# define IMG_GOM		("ressources/img/gom.png")
# define IMG_MAZE		("ressources/img/maze_sprites_important.png")
# define PAC_TRAP		("ressources/sound/menu_music.ogg")
# define EIGHTIES_MIX		("ressources/sound/80s_mix.ogg")
# define WAKA			("ressources/sound/waka.wav")
# define HIGH_SCORES		(".high-scores.txt")
# define HIGH_SCORES_TMP	(".hs-tmp.txt")
# define MAP			("ressources/maps/map_1.pc")
# define FONT			("ressources/font/font.ttf")

#endif				/* PARAMETERS_H_ */
