#ifndef DO_ENEMIES_H
#define DO_ENEMIES_H
#include<vector>

extern class Enemy
{
public:
	float xPos, yPos;
	float xVel,yVel;
	int Frame, FrameTime;
	int Active;
	int Facing;
	int ID;
	Enemy();
};

extern std::vector<Enemy> EnemyVector;
extern void CreateEnemy();
extern void DoEnemies();

#endif