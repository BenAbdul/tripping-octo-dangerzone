//Why did I name this Enemy projectiles?
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
			if ( XPOS < 500 || XPOS > 5500 || YPOS < 500 || YPOS > 5500) ACTIVE = 0;
			//if (ACTIVE == 0) ProjectileVector.erase(ProjectileVector.at(i),ProjectileVector.at(i + 7));
			FRAMETIME += 1;
			if(FRAMETIME == 2)
			{
				FRAMETIME = 0;
				FRAME += 1;
			}
			if(FRAME == 2) FRAME = 0;

			XPOS = XPOS + XRATIO;
			YPOS = YPOS + YRATIO;
			int LeFrame = FRAME;
			ApplySurface(XPOS - CameraX ,YPOS - CameraY,Projectile,Screen,&ProjectileClips[LeFrame]);
		}
	}
}
