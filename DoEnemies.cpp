#include"DoEnemies.h"
#include"Declarations.h"

Enemy::Enemy()
{
	if(CameraX > 2500) xPos = CameraX - 10;
	else xPos = CameraX + 10;

	if(CameraY > 2500) yPos = CameraY;
	else yPos = CameraY + 10;

	xVel = 0;
	yVel = 0;
	Active = 1;
}

std::vector<Enemy> EnemyVector;


#define CURRENTCLASS EnemyVector.at(x)
void DoEnemies()
{
	if(EnemyVector.size() >= 1)
	{
		for(int x = 0; x < EnemyVector.size(); x++)
		{
			if(CURRENTCLASS.xPos > PlayerX + 100 && CURRENTCLASS.xVel >= -5) 
			{
				CURRENTCLASS.xVel--;
				SpareStream.str("");
				SpareStream << "Enemy xPos " << CURRENTCLASS.xPos << " is more than player xPos " << PlayerX;
				OpenDebugWindow(SpareStream.str());
			}
			else if (CURRENTCLASS.xPos < PlayerX + 100 && CURRENTCLASS.xVel <= 5) 
			{
				CURRENTCLASS.xVel++;
				SpareStream.str("");
				SpareStream << "Enemy xPos " << CURRENTCLASS.xPos << " is less than player xPos " << PlayerX;
				OpenDebugWindow(SpareStream.str());
			}
			
			if(CURRENTCLASS.yPos > PlayerY + 100 && CURRENTCLASS.yVel >= -5) 	
			{
				CURRENTCLASS.yVel--;
				SpareStream.str("");
				SpareStream << "Enemy yPos " << CURRENTCLASS.yPos << " is more than player yPos " << PlayerY;
				OpenDebugWindow(SpareStream.str());
			}
			else if (CURRENTCLASS.yPos < PlayerY + 100 && CURRENTCLASS.yVel <= 5) 
			{
				CURRENTCLASS.yVel++;
				SpareStream.str("");
				SpareStream << "Enemy yPos " << CURRENTCLASS.yPos << " is less than player yPos " << PlayerY;
				OpenDebugWindow(SpareStream.str());
			}

			CURRENTCLASS.xPos += CURRENTCLASS.xVel;
			CURRENTCLASS.yPos += CURRENTCLASS.yVel;

			int OtherX = CameraX - CURRENTCLASS.xPos; //Easier to debug when this inevitably doesn't werk
			int OtherM = CameraY - CURRENTCLASS.yPos;
			ApplySurface(OtherX,OtherM, D1, Screen);
		}
	}
}
void CreateEnemy()
{
	Enemy TopLel;
	EnemyVector.push_back(TopLel);
}