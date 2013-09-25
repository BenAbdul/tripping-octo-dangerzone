#include"DoEnemies.h"
#include"Declarations.h"

Enemy::Enemy()
{
	if(CameraX > 2500) xPos = CameraX - 100;
	else xPos = CameraX + 10;

	if(CameraY > 2500) yPos = CameraY - 100;
	else yPos = CameraY + 10;

	xVel = 0;
	yVel = 0;
	Active = 1;
}

std::vector<Enemy> EnemyVector;

void CreateEnemy()
{
	Enemy TopLel;
	EnemyVector.push_back(TopLel);
}