
#include "game.h"
#include "map.h"
#include "physics.h"
#include "graphics.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts)
{
	srand(time(NULL));
	FILE* file = fopen(filename, "r");
	fscanf(file, "%d%d", &outMap->height, &outMap->width);
	int i, j;
	outGame->cheeses = outGame->cherries = outGame->pineapples = 0;
	for (i = 0; i < outMap->height; i++)
	{
		fscanf(file, "%*c");
		for (j = 0; j < outMap->width; j++)
		{
			fscanf(file, "%c", &outMap->cells[j][i]);
			switch (outMap->cells[j][i])
			{
				case CELL_CHERRY :
					outGame->cherries++;
					break;
				case CELL_CHEESE :
					outGame->cheeses++;
					break;
				case CELL_PINEAPPLE :
					outGame->pineapples++;
					break;
			}
		}
	}
	outPacman->speed = PACMAN_DEFAULT_SPEED;
	fscanf(file, "%d", &outGame->score);
	fscanf(file, "%*s %d %d (%d,%d) (%d,%d)", &outPacman->dir, &outPacman->health, &outPacman->startY, &outPacman->startX, &outPacman->y, &outPacman->x);
	outPacman->startX *= CELL_SIZE;
	outPacman->startX += (CELL_SIZE - OBJECT_SIZE) / 2;
	outPacman->startY *= CELL_SIZE;
	outPacman->startY += (CELL_SIZE - OBJECT_SIZE) / 2;
	outPacman->x *= CELL_SIZE;
	outPacman->x += (CELL_SIZE - OBJECT_SIZE) / 2;
	outPacman->y *= CELL_SIZE;
	outPacman->y += (CELL_SIZE - OBJECT_SIZE) / 2;
	for (i = 0; i < GHOST_COUNT; i++)
	{
		fscanf(file, "%*s %d %d", &outGhosts[i].dir, &outGhosts[i].blue);
		outGhosts[i].blueCounterDown = 0;
		if (!outGhosts[i].blue)
		{
			outGhosts[i].blue = 1;
			fscanf(file, "%d", &outGhosts[i].blueCounterDown);
		}
		outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
		fscanf(file, " (%d,%d) (%d,%d)", &outGhosts[i].startY, &outGhosts[i].startX, &outGhosts[i].y, &outGhosts[i].x);
		outGhosts[i].startX *= CELL_SIZE;
		outGhosts[i].startX += (CELL_SIZE - OBJECT_SIZE) / 2;
		outGhosts[i].startY *= CELL_SIZE;
		outGhosts[i].startY += (CELL_SIZE - OBJECT_SIZE) / 2;
		outGhosts[i].x *= CELL_SIZE;
		outGhosts[i].x += (CELL_SIZE - OBJECT_SIZE) / 2;
		outGhosts[i].y *= CELL_SIZE;
		outGhosts[i].y += (CELL_SIZE - OBJECT_SIZE) / 2;
		outGhosts[i].type = i;
		outGhosts[i].speed = GHOST_DEFAULT_SPEED;
	}
	fclose(file);
}

void checkEatables(Map* map, Game* outGame, const Pacman* pacman, Ghost* outGhosts, SDL_Surface* surface)
{
	int i, j;
	Uint32* pixels = (Uint32*) surface->pixels;
	SDL_Rect a;
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		for (j = 0; j < OBJECT_SIZE; j++)
		{
			int x = (i + pacman->x) % surface->w;
			int y = (j + pacman->y) % surface->h;
			a.x = x / CELL_SIZE * CELL_SIZE;
			a.y = y / CELL_SIZE * CELL_SIZE;
			a.w = a.h = CELL_SIZE;
			if (map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] == CELL_CHEESE && pixels[y * surface->w + x] == COLOR_CHEESE)
			{
					outGame->cheeses--;
					outGame->score += CHEESE_SCORE;
					map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] = CELL_EMPTY;
			}
			if (map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] == CELL_CHERRY && pixels[y * surface->w + x] == COLOR_CHERRY)
			{
					outGame->cherries--;
					outGame->score += CHERRY_SCORE;
					map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] = CELL_EMPTY;
			}
			if (map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] == CELL_PINEAPPLE && pixels[y * surface->w + x] == COLOR_PINEAPPLE)
			{
					outGame->pineapples--;
					outGame->score += PINEAPPLE_SCORE;
					map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE] = CELL_EMPTY;
					int k;
					for (k = 0; k < GHOST_COUNT; k++)
					{
						if (outGhosts[k].blue)
							outGhosts[k].blueCounterDown = BLUE_DURATION;
						outGhosts[k].blue = true;
						outGhosts[k].blueCounterDown += BLUE_DURATION;
					}
			}
		}
	}
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost, const SDL_Surface* surface)
{
	int i;
	int x = outPacman->x, y = outPacman->y;
	bool xMid, yMid;
	xMid = yMid = false;
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		if (x == outGhost->x || x == (outGhost->x + OBJECT_SIZE - 1) % surface->w)
			xMid = true;
		x = (x + 1) % surface->w;
	}
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		if (y == outGhost->y || y == (outGhost->y + OBJECT_SIZE - 1) % surface->h)
			yMid = true;
		y = (y + 1) % surface->h;
	}
	if (xMid && yMid)
	{
		if (outGhost->blue)
		{
			outGhost->x = outGhost->startX;
			outGhost->y = outGhost->startY;
			outGhost->blue = false;
			outGhost->blueCounterDown = 0;
		}
		else
		{
			outPacman->x = outPacman->startX;
			outPacman->y = outPacman->startY;
			outPacman->health--;
		}
		return;
	}
	x = outGhost->x;
	y = outGhost->y;
	xMid = yMid = false;
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		if (x == outPacman->x || x == (outPacman->x + OBJECT_SIZE - 1) % surface->w)
			xMid = true;
		x = (x + 1) % surface->w;
	}
	for (i = 0; i < OBJECT_SIZE; i++)
	{
		if (y == outPacman->y || y == (outPacman->y + OBJECT_SIZE - 1) % surface->h)
			yMid = true;
		y = (y + 1) % surface->h;
	}
	if (xMid && yMid)
	{
		if (outGhost->blue)
		{
			outGhost->x = outGhost->startX;
			outGhost->y = outGhost->startY;
			outGhost->blue = false;
			outGhost->blueCounterDown = 0;
		}
		else
		{
			outPacman->x = outPacman->startX;
			outPacman->y = outPacman->startY;
			outPacman->health--;
		}
		return;
	}
}

bool isGameFinished(const Game* game, const Pacman* pacman)
{
	if (game->cheeses + game->pineapples == 0)
		return true;
	if (!pacman->health)
		return true;
	return false;
}

void updateGhostState(Ghost* ghost)
{
	if (ghost->blue)
	{
		if (!ghost->blueCounterDown)
			ghost->blue = false;
		else
			ghost->blueCounterDown--;
	}
}

