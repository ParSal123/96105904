
#include "input.h"
#include "physics.h"

#include <stdio.h>
#include <time.h>

Direction decideGhost(const Map* map, Ghost* ghost)
{
	Direction dir;
	int x, y;
	do
	{
		x = ghost->x;
		y = ghost->y;
		dir = rand() % 4 + 1;
		switch (dir)
		{
			case DIR_UP:
				y--;
				break;
			case DIR_DOWN:
				y++;
				break;
			case DIR_RIGHT:
				x++;
				break;
			case DIR_LEFT:
				x--;
				break;
		}
		x = (x + map->width) % map->width;
		y = (y + map->height) % map->height;
	} while (map->cells[x][y] == CELL_BLOCK);	
	return dir;
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

