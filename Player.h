#ifndef PLAYER_H
#define PLAYER_H
#include"Declarations.h"


class Player
{
public:
	int Lives;
	int Ammo;
	int CurrentSelection;

	int xVel, yVel;
	float xPos, yPos;
	int WorldxPos, WorldyPos;

	SDL_Surface *CurrentSprite;

	void HandleEvents();
	void UpdatePosition();
	void Fire();

	Player();
};

#endif