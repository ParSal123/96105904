
#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "input.h"
#include "game.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map* map, Pacman* pacman, Action action);

// TO WRITE
Direction decideGhost(const Map* map, Ghost* ghost, Pacman* pacman, Ghost* blinky);
Direction decideBlinky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decidePinky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideInky(const Map*, const Ghost*, const Pacman*, const Ghost*, const Ghost*);
Direction decideClyde(const Map*, const Ghost*, const Pacman*, const Ghost*);

#endif

