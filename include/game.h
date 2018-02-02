
#ifndef __GAME_H
#define __GAME_H

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "map.h"

typedef enum
{ 
    DIR_UP    = 1,
    DIR_RIGHT = 2,
    DIR_DOWN  = 3,
    DIR_LEFT  = 4,
    DIR_NONE  = 0
} Direction;

typedef enum { BLINKY, PINKY, INKY, CLYDE} GhostType;

#define GHOST_COUNT 4
#define CHEESE_SCORE 10
#define CHERRY_SCORE 100
#define PINEAPPLE_SCORE 20

#define BLUE_DURATION 5 * CYCLES_PER_SEC

#define COLLISION_DIST 0.4

typedef struct
{
	int score;
	int cheeses, cherries, pineapples;
	int time;
} Game;

typedef struct
{
	int x, y;
	int startX, startY;
	Direction dir;
	int health;
	double speed;
} Pacman;

typedef enum { SCATTER, CHASE } GhostState;

typedef struct
{
	int x, y;
	int startX, startY;
	Direction dir;
	GhostType type;
	bool blue;
	GhostState state;
	unsigned long long blueCounterDown;
	unsigned long long stateCounterDown;
	double speed;
} Ghost;

void initiateGame(char*, Map*, Game*, Pacman*, Ghost*);
void checkEatables(Map*, Game*, const Pacman*, Ghost*, SDL_Surface*);
void checkGhostCollision(Pacman*, Ghost*, const SDL_Surface*);
bool isGameFinished(const Game*, const Pacman*);
void updateGhostState(Ghost*);

#endif

