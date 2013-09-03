#include "DoEnemyProjectiles.h"
#include "Declarations.h"

#define XPOS		ProjectileVector.at(i)
#define YPOS		ProjectileVector.at(i + 2)
#define FRAME		ProjectileVector.at(i + 3)
#define FRAMETIME	ProjectileVector.at(i + 4)
#define XRATIO		ProjectileVector.at(i + 5)
#define YRATIO		ProjectileVector.at(i + 6)
#define ACTIVE		ProjectileVector.at(i + 7)

/*
Series for projectile vector
... xPos,yPos,Frame,Frametime,xRatio,yRatio,Active ... (7 variables)
	= x										 = x+6
*/

void DoEnemyProjectiles()
{
	if (ProjectileVector.size() > 6)
	{
		for(int i = 0; i <= ProjectileVector.size() - 6; i+=7)
		{
			if(ACTIVE == 0) continue;

			XPOS += XRATIO;
			YPOS += YRATIO;

			ApplySurface(XPOS,YPOS,Projectile,Screen);
		}
	}
}
