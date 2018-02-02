
#include "game.h"
#include "graphics.h"
#include "map.h"
#include "physics.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

Map *map;
Game *game;
Ghost *ghosts;
Pacman *pacman;

SDL_Window* window;
SDL_Surface* surface;

void initiate()
{
	map = malloc(sizeof(Map));
	game = malloc(sizeof(Game));
	ghosts = malloc(GHOST_COUNT * sizeof(Ghost));
	pacman = malloc(sizeof(Pacman));
	char* filename = "../res/reality.txt";
	initiateGame(filename, map, game, pacman, ghosts);
	initiateSDL(&window, &surface, map->width, map->height);
	drawBoard(map, surface);
	game->time = 0;
}

int main()
{
	initiate();
	SDL_Event event;
	int delay = 1000 / CYCLES_PER_SEC;
	int i;
	while (!isGameFinished(game, pacman))
	{
		drawPacman(pacman, map, surface);
		drawGhosts(ghosts, map, surface);
		SDL_UpdateWindowSurface(window);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				terminate(window, surface);
			if (event.type == SDL_KEYDOWN)
			{
				Direction dir;
				switch (event.key.keysym.sym)
				{
					case SDLK_UP :
						dir = DIR_UP;
						break;
					case SDLK_RIGHT :
						dir = DIR_RIGHT;
						break;
					case SDLK_DOWN :
						dir = DIR_DOWN;
						break;
					case SDLK_LEFT :
						dir = DIR_LEFT;
						break;
					default :
						break;
				}
				pacman->dir = decidePacman(pacman, dir, surface);
			}
		}
		pacman->dir = decidePacman(pacman, pacman->dir, surface);
//		for (i = 0; i < GHOST_COUNT; i++)
//			ghosts[i].dir = decideGhost(map, ghosts + i, pacman, ghosts, surface);
		updateBoard(surface, map, pacman, ghosts);
		movePacman(pacman, surface);
//		moveGhosts(ghosts, surface);
		checkEatables(map, game, pacman, ghosts, surface);
		for (i = 0; i < GHOST_COUNT; i++)
			checkGhostCollision(pacman, ghosts + i, surface);
		updateBoard(surface, map, pacman, ghosts);
		for (i = 0; i < GHOST_COUNT; i++)
			updateGhostState(ghosts + i);
		SDL_Delay(delay);
		game->time += delay;
	}
	return 0;
}

