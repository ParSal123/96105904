
#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include "game.h"
#include "map.h"

#include <SDL2/SDL.h>

#define CELL_SIZE      36
#define CHEESE_SIZE    10
#define PINEAPPLE_SIZE 18
#define CHERRY_SIZE    16
#define OBJECT_SIZE    26

#define CYCLES_PER_SEC 500

Uint32 COLOR_PACMAN, COLOR_BLOCK, COLOR_EMPTY, COLOR_CHEESE, COLOR_PINEAPPLE, COLOR_CHERRY;

void initiateSDL(SDL_Window**, SDL_Surface**, int, int);
void fillRect(SDL_Surface*, const SDL_Rect*, Uint32);
void updateCell(SDL_Surface*, Map*, int, int);
void updateBoard(SDL_Surface*, Map*, const Pacman*, const Ghost*);
void terminate(SDL_Window*, SDL_Surface*);
void drawBoard(const Map*, SDL_Surface*);
void drawPacman(const Pacman*, const Map*, SDL_Surface*);
void drawGhosts(const Ghost*, const Map*, SDL_Surface*);

#endif

