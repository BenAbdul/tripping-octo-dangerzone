#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
	int Lives;
	int Ammo;
	int CurrentSelection;

	int xVel, yVel;
	int xPos, yPos;
	int WorldxPos, WorldyPos;

	void HandleEvents();
	void UpdatePosition();
	void Fire();

	Player();
};

#endif