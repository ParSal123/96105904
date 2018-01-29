
#include "input.h"
#include "map.h"
#include "physics.h"

#include <float.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int toInt(double x)
{
	int n = round(x);
	if (abs(n - x) <= DBL_EPSILON)
		return n;
	return n + 1;
}

Direction bfs(const Map* map, Node u, Node v)
{
	bool mark[MAP_MAX_SIZE][MAP_MAX_SIZE];
	Direction par[MAP_MAX_SIZE][MAP_MAX_SIZE];
	Node queue[1000000];
	int size = 0, index = 0;
	int dx[5] = {0, 0, -1, 0, 1};
	int dy[5] = {0, 1, 0, -1, 0};
	memset(mark, false, sizeof(bool) * MAP_MAX_SIZE * MAP_MAX_SIZE);
	queue[size++] = v;
	par[v.x][v.y] = DIR_NONE;
	mark[v.x][v.y] = true;
	while (index < size)
	{
		Node temp = queue[index];
		int i;
		for (i = 1; i <= 4; i++)
		{
			temp.x = (temp.x + dx[i] + map->width) % map->width;
			temp.y = (temp.y + dy[i] + map->height) % map->height;
			if (!mark[temp.x][temp.y] && map->cells[temp.x][temp.y] != CELL_BLOCK)
			{
				mark[temp.x][temp.y] = true;
				queue[size++] = temp;
				par[temp.x][temp.y] = i;
			}
			temp.x = (temp.x - dx[i] + map->width) % map->width;
			temp.y = (temp.y - dy[i] + map->height) % map->height;
		}
		index++;
	}
	return par[u.x][u.y];
}

Direction decideRandom(const Map* map, const Ghost* ghost)
{
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int dir, x, y;
	do
	{
		dir = rand() % 4 + 1;
		x = (toInt(ghost->x) + dx[dir]) % map->width;
		y = (toInt(ghost->y) + dx[dir]) % map->height;
	}
	while (map->cells[x][y] == CELL_BLOCK);
	return dir;
}

Direction decideBlinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	Node ghostPos, pacmanPos;
	ghostPos.x = toInt(ghost->x);
	ghostPos.y = toInt(ghost->y);
	pacmanPos.x = toInt(pacman->x);
	pacmanPos.y = toInt(pacman->y);
	return bfs(map, ghostPos, pacmanPos);
}

Direction decidePinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	Node ghostPos, destPos; // destinationPos
	ghostPos.x = toInt(ghost->x);
	ghostPos.y = toInt(ghost->y);
	destPos.x = toInt(pacman->x);
	destPos.y = toInt(pacman->y);
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int i;
	for (i = 1; i <= 5; i++)
	{
		destPos.x = (destPos.x + dx[i] + map->width) % map->width;
		destPos.y = (destPos.y + dy[i] + map->height) % map->height;
		if (map->cells[destPos.x][destPos.y] == CELL_BLOCK)
			break;
	}
	destPos.x = (destPos.x - dx[i] + map->width) % map->width;
	destPos.y = (destPos.y - dy[i] + map->height) % map->height;
	return bfs(map, ghostPos, destPos);
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

