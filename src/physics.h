
#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "input.h"
#include "game.h"

#define PACMAN_DEFAULT_SPEED 2.
#define GHOST_DEFAULT_SPEED 2.

// TO WRITE
Direction decidePacman(const Map*, Pacman*, Action);

// TO WRITE
Direction decideGhost(const Map*, Ghost*, Pacman*, Ghost*);
Direction decideBlinky(const Map*, const Ghost*, const Pacman*);
Direction decidePinky(const Map*, const Ghost*, const Pacman*);
Direction decideInky(const Map*, const Ghost*, const Pacman*, const Ghost*);
Direction decideClyde(const Map*, const Ghost*, const Pacman*);

#endif

