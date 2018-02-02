
#include "graphics.h"
#include "map.h"
#include "physics.h"

#include <float.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
/*
Direction bfs(const Map* map, Node u, Node v)
{
	bool mark[MAP_MAX_SIZE][MAP_MAX_SIZE];
	Direction par[MAP_MAX_SIZE][MAP_MAX_SIZE];
	Node queue[100000];
	int size = 0, top = 0;
	int dx[5] = {0, 0, -1, 0, 1};
	int dy[5] = {0, 1, 0, -1, 0};
	memset(mark, false, sizeof(bool) * MAP_MAX_SIZE * MAP_MAX_SIZE);
	queue[size++] = v;
	par[v.x][v.y] = DIR_NONE;
	mark[v.x][v.y] = true;
	while (top < size)
	{
		Node temp = queue[top];
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
		top++;
	}
	return par[u.x][u.y];
}

Direction decideRandom(const Map* map, const Ghost* ghost)
{
	int i;
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int dir, x, y;
	do
	{
		dir = rand() % 4 + 1;
		x = (toInt(ghost->x) + dx[dir] + map->width) % map->width;
		y = (toInt(ghost->y) + dx[dir] + map->height) % map->height;
	}
	while (map->cells[x][y] == CELL_BLOCK);
	return dir;
}

Direction decideBlinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	Node ghostPos, pacmanPos;
	ghostPos = getPos(ghost->x, ghost->y);
	pacmanPos = getPos(pacman->x, pacman->y);
	return bfs(map, ghostPos, pacmanPos);
}

Direction decidePinky(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	Node ghostPos, destPos; // destinationPos
	ghostPos = getPos(ghost->x, ghost->y);
	destPos = getPos(pacman->x, pacman->y);
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int i;
	for (i = 1; i <= 5; i++)
	{
		destPos.x = (destPos.x + dx[pacman->dir] + map->width) % map->width;
		destPos.y = (destPos.y + dy[pacman->dir] + map->height) % map->height;
		if (map->cells[destPos.x][destPos.y] == CELL_BLOCK)
			break;
	}
	destPos.x = (destPos.x - dx[pacman->dir] + map->width) % map->width;
	destPos.y = (destPos.y - dy[pacman->dir] + map->height) % map->height;
	return bfs(map, ghostPos, destPos);
}

Direction decideInky(const Map* map, const Ghost* ghost, const Pacman* pacman, const Ghost* blinky)
{
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	Node ghostPos, pacmanPos, blinkyPos;
	ghostPos = getPos(ghost->x, ghost->y);
	pacmanPos = getPos(pacman->x, pacman->y);
	blinkyPos = getPos(blinky->x, blinky->y);
	pacmanPos.x += 2 * dx[pacman->dir];
	pacmanPos.y += 2 * dy[pacman->dir];
	int xDiff = pacmanPos.x - blinkyPos.x;
	int yDiff = pacmanPos.y - blinkyPos.y;
	Node destPos;
	destPos.x = (blinkyPos.x + 2 * xDiff + 2 * map->width) % map->width;
	destPos.y = (blinkyPos.y + 2 * yDiff + 2 * map->height) % map->height;
	if (map->cells[destPos.x][destPos.y] == CELL_BLOCK)
		return decideRandom(map, ghost);
	return bfs(map, ghostPos, destPos);
}

Direction decideClyde(const Map* map, const Ghost* ghost, const Pacman* pacman)
{
	Node ghostPos, pacmanPos; // destinationPos
	ghostPos = getPos(ghost->x, ghost->y);
	pacmanPos = getPos(pacman->x, pacman->y);
	if (abs(ghostPos.x - pacmanPos.x) + abs(ghostPos.y - pacmanPos.y) > 8)
		return bfs(map, ghostPos, pacmanPos);
	if (map->cells[0][map->height - 1] != CELL_BLOCK)
	{
		Node destPos = getPos(0, map->height - 1);
		return bfs(map, ghostPos, destPos);
	}
	return decideRandom(map, ghost);
}
*/

/*Direction decideGhost(const Map* map, const Ghost* ghost, const Pacman* pacman, const Ghost* blinky, const SDL_Surface* surface)
{
	Direction dir = ghost->type;
	return isDirectionValid(dir, surface, ghost->x, ghost->y) ? dir : 0;
}*/
	/*
	if (ghost->blue)
	{
		Node ghostPos, ghostStartPos;
		ghostPos = getPos(ghost->x, ghost->y);
		ghostStartPos = getPos(ghost->startX, ghost->startY);
		return bfs(map, ghostPos, ghostStartPos);
	}
	switch (ghost->type)
	{
		case BLINKY :
			//return decideBlinky(map, ghost, pacman);
			return -1;
		case PINKY :
	return -1;
			//return decidePinky(map, ghost, pacman);
		case INKY :
	return -1;
			//return decideInky(map, ghost, pacman, blinky);
		case CLYDE :
			return decideClyde(map, ghost, pacman);
	}
}
*/
bool isDirectionValid(Direction dir, const SDL_Surface* surface, int x, int y)
{
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int x1, y1;
	int x2;
	int y2 = (y + OBJECT_SIZE - 1) % surface->h;
	int i;
	Uint32* pixels = (Uint32*) surface->pixels;
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		x2 = (x + i) % surface->w;
		if (pixels[y * surface->w + x2] == COLOR_BLOCK)
			return false;
		if (pixels[y2 * surface->w + x2] == COLOR_BLOCK)
			return false;
	}
	x2 = (x + OBJECT_SIZE - 1) % surface->w;
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		y2 = (y + i) % surface->h;
		if (pixels[y2 * surface->w + x] == COLOR_BLOCK)
			return false;
		if (pixels[y2 * surface->w + x2] == COLOR_BLOCK)
			return false;
	}
	return true;
}

Direction decidePacman(Pacman* pacman, Direction dir, const SDL_Surface* surface)
{
	int x = pacman->x, y = pacman->y;
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
	return isDirectionValid(dir, surface, x, y) ? dir : 0;
}

void movePacman(Pacman* pacman, const SDL_Surface* surface)
{
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int x = pacman->x, y = pacman->y;
	x += dx[pacman->dir];
	y += dy[pacman->dir];
	x = (x + surface->w) % surface->w;
	y = (y + surface->h) % surface->h;
	pacman->x = x;
	pacman->y = y;
}

void moveGhosts(Ghost* ghosts, const SDL_Surface* surface)
{
	int dx[5] = {0, 0, 1, 0, -1};
	int dy[5] = {0, -1, 0, 1, 0};
	int i;
	for (i = 0; i < GHOST_COUNT; i++)
	{
		int x = ghosts[i].x, y = ghosts[i].y;
		x += dx[ghosts[i].dir];
		y += dy[ghosts[i].dir];
		x = (x + surface->w) % surface->w;
		y = (y + surface->h) % surface->h;
		ghosts[i].x = x;
		ghosts[i].y = y;
	}
}

