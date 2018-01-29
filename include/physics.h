
#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "input.h"
#include "game.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

typedef struct
{
	int x, y;
} Node;

int toInt(double);

Direction decidePacman(const Map*, Pacman*, Action);

Direction bfs(const Map*, Node, Node);
Direction decideGhost(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideRandom(const Map*, const Ghost*);
Direction decideBlinky(const Map*, const Ghost*, const Pacman*);
Direction decidePinky(const Map*, const Ghost*, const Pacman*);
Direction decideInky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideClyde(const Map*, const Ghost*, const Pacman*);

#endif

