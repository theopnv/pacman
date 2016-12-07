#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "menu.h"
#include "parameters.h"

static int	insert(t_exe *exe, FILE *new_file)
{
  char		*line;
  char		new_score[SCORE_LENGTH];

  if (!(line = calloc(LINE_LENGTH, sizeof(char))))
   return (EXIT_FAILURE);
  line = strcpy(line, exe->player.pseudo);
  line = remove_underscores(line);
  strcat(line, ";");
  if (snprintf(new_score, 9, "%d", exe->game.score.score) < 0)
    return (err_c(errno));
  strcat(line, new_score);
  strcat(line, "\n");
  if (fwrite(line, strlen(line), 1, new_file) <= 0)
    return (err_c(errno));
  free(line);
  return (EXIT_SUCCESS);
}

static int	copy(FILE *new_file, char *line)
{
  int		endline;

  endline = strlen(line);
  if (!(line = realloc(line, endline + 2)))
    return (EXIT_FAILURE);
  line[endline] = '\n';
  line[endline + 1] = '\0';
  if (fwrite(line, (endline + 1), 1, new_file) <= 0)
    return (err_c(errno));
  free(line);
  return (EXIT_SUCCESS);
}

static int	copy_text(t_exe *exe, int file, FILE *new_file, const int excepted)
{
  char		*line;
  int		i;

  for (i = 0; i < NB_HIGH_SCORES; i++)
    {
      if (!(line = get_next_line(file)))
	return (EXIT_FAILURE);
      if (i == excepted
	  && insert(exe, new_file) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      else if (i != excepted
	  && copy(new_file, line) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  if (close(file) == SYS_ERR
     || fclose(new_file) == EOF)
   return (err_c(errno));
  return (EXIT_SUCCESS);
}

static int	update_high_scores(t_exe *exe)
{
  FILE		*new_file;
  int		file;
  int		excepted;

  if (!(file = open(HIGH_SCORES, O_RDONLY))
      || !(new_file = fopen(HIGH_SCORES_TMP, "w")))
    return (err_c(errno));
  if ((excepted = get_score_to_delete(exe, file)) == NOT_IN_HS)
    {
      init_active(exe, MENU);
      return (EXIT_SUCCESS);
     }
  if (lseek(file, 0, SEEK_SET) < 0)
    return (err_c(errno));
  if (copy_text(exe, file, new_file, excepted) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (remove(HIGH_SCORES) == SYS_ERR
      || rename(HIGH_SCORES_TMP, HIGH_SCORES) == SYS_ERR)
    return (err_c(errno));
  init_active(exe, MENU);
    return (EXIT_SUCCESS);
}

int		get_pseudo(t_exe *exe)
{
  char		*key;
  int		stop = 0;
  SDL_Event	tmp;

  while (!stop)
    {
      SDL_WaitEvent(&tmp);
      if (tmp.type == SDL_KEYDOWN)
	{
	   switch (tmp.key.keysym.sym)
	     {
		case SDLK_ESCAPE:
		  escape(exe);
		  break;
		case SDLK_RETURN:
		  if (update_high_scores(exe) == EXIT_FAILURE)
		    return (EXIT_FAILURE);
		  break;
		case SDLK_BACKSPACE:
		  --exe->player.i;
		  if (exe->player.i < 0)
		    exe->player.i = 0;
		  exe->player.pseudo[exe->player.i] = '_';
		  break;
		default:
		  if (exe->player.i < PSEUDO_LENGTH - 1)
		    {
		      key = SDL_GetKeyName(tmp.key.keysym.sym);
		      if (key[1] == '\0') /* Block non-alphanumeric keys */
			{
			  exe->player.pseudo[exe->player.i] =
			  SDL_GetKeyName(tmp.key.keysym.sym)[0];
			  ++exe->player.i;
			}
		    }
		  break;
	     }
	  stop = 1;
	}
    }
  return (EXIT_SUCCESS);
}
