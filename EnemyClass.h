#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

class Enemy
{
public:
	float xPos, yPos;
	float xVel,yVel;
	float Random;
	int Frame, FrameTime;
	int Active; 
	int Facing;
	int ID;
	Enemy();
};

#endif