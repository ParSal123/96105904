
#include "game.h"
#include "map.h"
#include "physics.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts)
{
    srand(time(NULL));
    FILE* file = fopen("../res/map.txt", "r");
    fscanf(file, "%d%d", &outMap->height, &outMap->width);
    int i, j;
    outGame->cheeses = outGame->cherries = outGame->pineapples = 0;
    outGame->ghosts = 4;
    for (i = 0; i < outMap->height; i++)
    {
        fscanf(file, "%*c");
        for (j = 0; j < outMap->width; j++)
        {
            fscanf(file, "%c", &outMap->cells[j][i]);
            switch (outMap->cells[j][i])
            {
                case CELL_CHERRY:
                    outGame->cherries++;
                    break;
                case CELL_CHEESE:
                    outGame->cheeses++;
                    break;
                case CELL_PINEAPPLE:
                    outGame->pineapples++;
                    break;
            }
		}
    }
	outPacman->speed = PACMAN_DEFAULT_SPEED;
    fscanf(file, "%d", &outGame->score);
    fscanf(file, "%*s %d %d (%d,%d) (%lf,%lf)", &outPacman->dir, &outPacman->health, &outPacman->startY, &outPacman->startX, &outPacman->y, &outPacman->x);
	for (i = 0; i < outGame->ghosts; i++)
	{
		fscanf(file, "%*s %d %d", &outGhosts[i].dir, &outGhosts[i].blue);
		outGhosts[i].blueCounterDown = 0;
		if (!outGhosts[i].blue)
		{
			outGhosts[i].blue = 1;
			fscanf(file, "%d", &outGhosts[i].blueCounterDown);
		}
		outGhosts[i].blueCounterDown *= CYCLES_PER_SEC;
		fscanf(file, " (%d,%d) (%lf,%lf)", &outGhosts[i].startY, &outGhosts[i].startX, &outGhosts[i].y, &outGhosts[i].x);
		outGhosts[i].type = i;
		outGhosts[i].speed = GHOST_DEFAULT_SPEED;
	}
	fclose(file);
}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts)
{
	int i, j;
	const double COLLISION_DIST = 0.4;
	for (i = 0; i < map->width; i++)
		for (j = 0; j < map->height; j++)
		{
			double distX = outPacman->x - i;
			double distY = outPacman->y - j;
			if (sqrt(distX * distX + distY * distY) < COLLISION_DIST)
			{
				switch (map->cells[i][j])
				{
					case CELL_CHEESE:
						outGame->cheeses--;
						outGame->score += CHEESE_SCORE;
						break;
					case CELL_CHERRY:
						outGame->cherries--;
						outGame->score += CHERRY_SCORE;
						break;
					case CELL_PINEAPPLE:
						outGame->pineapples--;
						outGame->score += PINEAPPLE_SCORE;
						int k;
						for (k = 0; k < outGame->ghosts; k++)
						{
							if (outGhosts[k].blue)
								outGhosts[k].blueCounterDown = BLUE_DURATION;
							outGhosts[k].blue = true;
							outGhosts[k].blueCounterDown += BLUE_DURATION;
						}
						break;
				}
				map->cells[i][j] = CELL_EMPTY;
			}
		}
}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost)
{
	const double COLLISION_DIST = 0.4;
	double distX = outPacman->x - outGhost->x;
	double distY = outPacman->y - outGhost->y;
	if (sqrt(distX * distX + distY * distY) < COLLISION_DIST)
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
}

bool isGameFinished(Game* game, Pacman* pacman)
{
	if (game->cheeses + game->pineapples == 0)
		return true;
	if (!pacman->health)
		return true;
	return false;
}

void checkGhostState(Ghost* ghost)
{
	if (ghost->blue)
	{
		if (!ghost->blueCounterDown)
			ghost->blue = false;
		else
			ghost->blueCounterDown--;
	}
}

