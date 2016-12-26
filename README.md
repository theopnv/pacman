# Pacman

This is a small project written in C on my free-time. It is still under development, and may not be playable with a full experience.

## Installation

To be compiled, this project requires the SDL librairy, plus SDL_ttf, SDL_image and SDL_mixer. Install them first on your system

* `$ make` to build the project and get the binary file.
* `$ make clean` to remove compilation files

To write available logs in the log file, execute the game with the `--debug` argument.

## Project

Updates are programmed to take place on a regular basis. On the first time, I'll focus on stability and performance updates, but very soon, new features will be implemented !
A public [Trello board](https://trello.com/b/x6A6RNEA) is linked to this repository. It lists all the updates soon available.  

## Map editor

The game is implemented in a way that lets you create your own map - though this feature may not be well supported. I built a "map code" with letter, which isn't very ergonomic, I know. If you want more details I advise you to look at how the default map is built, in ressources/maps/. Keep in mind that pacman maps always have to be 28 tiles large and 31 long.
