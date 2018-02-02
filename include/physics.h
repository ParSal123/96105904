
#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "game.h"
#include "graphics.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

typedef struct
{
	int x, y;
} Node;

int toInt(double);

Direction decidePacman(Pacman*, Direction, const SDL_Surface*);

bool isDirectionValid(Direction, const SDL_Surface*, int, int);
Direction bfs(const Map*, Node, Node);
Direction decideGhost(const Map*, const Ghost*, const Pacman*, const Ghost*, const SDL_Surface*);
Direction decideRandom(const Map*, const Ghost*);
Direction decideBlinky(const Map*, const Ghost*, const Pacman*);
Direction decidePinky(const Map*, const Ghost*, const Pacman*);
Direction decideInky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideClyde(const Map*, const Ghost*, const Pacman*);

void movePacman(Pacman*, const SDL_Surface*);
void moveGhosts(Ghost*, const SDL_Surface*);

#endif

