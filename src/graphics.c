
#include "game.h"
#include "graphics.h"
#include "map.h"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

void initiateSDL(SDL_Window** window, SDL_Surface** surface, int width,
	int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Could not initialize SDL. SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	*window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, CELL_SIZE * width, CELL_SIZE * height,
		SDL_WINDOW_SHOWN);
	if (!*window)
	{
		printf("Could not create window. SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	*surface = SDL_GetWindowSurface(*window);
	COLOR_PACMAN    = SDL_MapRGB((*surface)->format, 243, 255, 101);
	COLOR_BLOCK     = SDL_MapRGB((*surface)->format, 95, 122, 255);
	COLOR_EMPTY     = SDL_MapRGB((*surface)->format, 0, 0, 0);
	COLOR_CHEESE    = SDL_MapRGB((*surface)->format, 243, 177, 135);
	COLOR_PINEAPPLE = SDL_MapRGB((*surface)->format, 243, 177, 136);
	COLOR_CHERRY    = SDL_MapRGB((*surface)->format, 249, 59, 44);
}

void fillRect(SDL_Surface* surface, const SDL_Rect* rect, Uint32 color)
{
	int i, j;
	Uint32* pixels = (Uint32*) surface->pixels;
	for (i = 0; i < rect->w; i++)
		for (j = 0; j < rect->h; j++)
		{
			int x = (i + rect->x) % surface->w;
			int y = (j + rect->y) % surface->h;
			pixels[y * surface->w + x] = color;
		}
}

void updateCell(SDL_Surface* surface, Map* map, int x, int y)
{
	SDL_Rect a;
	a.x = x / CELL_SIZE * CELL_SIZE;
	a.y = y / CELL_SIZE * CELL_SIZE;
	a.w = a.h = CELL_SIZE;
	fillRect(surface, &a, COLOR_EMPTY);
	Uint32 color;
	switch (map->cells[a.x / CELL_SIZE][a.y / CELL_SIZE])
	{
		case CELL_CHERRY :
			color = COLOR_CHERRY;
			a.w = a.h = CHERRY_SIZE;
			break;
		case CELL_CHEESE :
			color = COLOR_CHEESE;
			a.w = a.h = CHEESE_SIZE;
			break;
		case CELL_PINEAPPLE :
			color = COLOR_PINEAPPLE;
			a.w = a.h = PINEAPPLE_SIZE;
			break;
		default :
			color = COLOR_EMPTY;
			break;
	}
	a.x += (CELL_SIZE - a.w) / 2;
	a.y += (CELL_SIZE - a.h) / 2;
	fillRect(surface, &a, color);
}

void updateBoard(SDL_Surface* surface, Map* map, const Pacman* pacman, const Ghost* ghosts)
{
	int i, j, k;
	int x, y;
	for (i = 0; i < OBJECT_SIZE; i += OBJECT_SIZE - 1)
		for (j = 0; j < OBJECT_SIZE; j += OBJECT_SIZE - 1)
		{
			x = (pacman->x + i) % surface->w;
			y = (pacman->y + j) % surface->h;
			updateCell(surface, map, x, y);
			for (k = 0; k < GHOST_COUNT; k++)
			{
				x = (ghosts[k].x + i) % surface->w;
				y = (ghosts[k].y + j) % surface->h;
				updateCell(surface, map, x, y);
			}
		}
}

void drawBoard(const Map* map, SDL_Surface* surface)
{
	int i, j;
	SDL_Rect a;
	int color;
	for (i = 0; i < map->width; i++)
		for (j = 0; j < map->height; j++)
		{
			switch (map->cells[i][j])
			{
				case CELL_CHERRY :
					color = COLOR_CHERRY;
					a.w = a.h = CHERRY_SIZE;
					break;
				case CELL_CHEESE :
					color = COLOR_CHEESE;
					a.w = a.h = CHEESE_SIZE;
					break;
				case CELL_PINEAPPLE :
					color = COLOR_PINEAPPLE;
					a.w = a.h = PINEAPPLE_SIZE;
					break;
				case CELL_BLOCK :
					color = COLOR_BLOCK;
					a.w = a.h = CELL_SIZE;
					break;
				default :
					color = COLOR_EMPTY;
					a.w = a.h = CELL_SIZE;
					break;
			}
			a.x = i * CELL_SIZE + (CELL_SIZE - a.w) / 2;
			a.y = j * CELL_SIZE + (CELL_SIZE - a.h) / 2;
			fillRect(surface, &a, color);
		}
}

void drawPacman(const Pacman* pacman, const Map* map, SDL_Surface* surface)
{
	int color = COLOR_PACMAN;
	SDL_Rect a;
	a.w = a.h = OBJECT_SIZE;
	a.x = pacman->x;
	a.y = pacman->y;
	fillRect(surface, &a, color);
}

void drawGhosts(const Ghost* ghosts, const Map* map, SDL_Surface* surface)
{
	SDL_Rect a;
	a.w = a.h = OBJECT_SIZE;
	int colors[4];
	colors[0] = SDL_MapRGB(surface->format, 249, 59, 44);
	colors[1] = SDL_MapRGB(surface->format, 255, 131, 206);
	colors[2] = SDL_MapRGB(surface->format, 80, 255, 255);
	colors[3] = SDL_MapRGB(surface->format, 246, 218, 65);
	int i;
	for (i = 0; i < GHOST_COUNT; i++)
	{
		a.x = ghosts[i].x;
		a.y = ghosts[i].y;
		fillRect(surface, &a, colors[i]);
	}
}

void terminate(SDL_Window* window, SDL_Surface* surface)
{
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

