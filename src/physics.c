
#include "input.h"
#include "physics.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

Direction decideBlinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	return DIR_NONE;
}

Direction decidePinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	return DIR_NONE;
}

Direction decideInky(const Map* map, const Ghost* ghost, const Pacman* pacman, const Ghost* blinky)
{
	return DIR_NONE;
}

Direction decideClyde(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	return DIR_NONE;
}

Direction decideGhost(const Map* map, const Ghost* ghost, const Pacman* pacman, const Ghost* blinky)
{
	switch (ghost->type)
	{
		case BLINKY:
			return decideBlinky(map, ghost, pacman);
		case PINKY:
			return decidePinky(map, ghost, pacman);
		case INKY:
			return decideInky(map, ghost, pacman, blinky);
		case CLYDE:
			return decideClyde(map, ghost, pacman);
	}
}

Direction decidePacman(const Map* map, Pacman* pacman, Action action)
{
    int x = pacman->x, y = pacman->y;
	Direction dir;
	switch (MOVE_ACTION_MASK & action)
	{
		case ACTION_UP:
			dir = DIR_UP;
			y--;
			break;
		case ACTION_DOWN:
			y++;
			dir = DIR_DOWN;
			break;
		case ACTION_RIGHT:
			x++;
			dir = DIR_RIGHT;
			break;
		case ACTION_LEFT:
			x--;
			dir = DIR_LEFT;
			break;
	}
	x = (x + map->width) % map->width;
	y = (y + map->height) % map->height;
	if (map->cells[x][y] == CELL_BLOCK)
		dir = DIR_NONE;
	return dir;
}

