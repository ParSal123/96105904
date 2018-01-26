
#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "input.h"
#include "game.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map* map, Pacman* pacman, Action action);

// TO WRITE
Direction decideGhost(const Map* map, const Ghost* ghost, const Pacman* pacman, const Ghost* blinky);
Direction decideBlinky(const Map*, const Ghost*, const Pacman*);
Direction decidePinky(const Map*, const Ghost*, const Pacman*);
Direction decideInky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideClyde(const Map*, const Ghost*, const Pacman*);

#endif

