#include "DoEnemyProjectiles.h"
#include "Declarations.h"
#include "Camera.h"

#define XPOS		ProjectileVector.at(i)
#define YPOS		ProjectileVector.at(i + 1)
#define FRAME		ProjectileVector.at(i + 2)
#define FRAMETIME	ProjectileVector.at(i + 3)
#define XRATIO		ProjectileVector.at(i + 4)
#define YRATIO		ProjectileVector.at(i + 5)
#define ACTIVE		ProjectileVector.at(i + 6)

/*
Series for projectile vector
... xPos,yPos,Frame,Frametime,xRatio,yRatio,Active ... (7 variables)
	= x										 = x+6
*/

void DoEnemyProjectiles()
{
	if (ProjectileVector.size() > 6)
	{
		for(int i = 0; i <= ProjectileVector.size() - 7; i += 7)
		{
			if(ACTIVE == 0) continue;

			XPOS += XRATIO;
			YPOS += YRATIO;

			ApplySurface(YPOS - CameraX ,YPOS - CameraY,Projectile,Screen);
		}
	}
}
