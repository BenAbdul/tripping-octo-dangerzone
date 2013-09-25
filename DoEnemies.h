#ifndef DO_ENEMIES_H
#define DO_ENEMIES_H
#include<vector>

extern class Enemy
{
public:
	int xPos, yPos;
	int xVel,yVel;
	int Active;
	Enemy();
};

extern void CreateEnemy();
extern void DoEnemies();

#endif