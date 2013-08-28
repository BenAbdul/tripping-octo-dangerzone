#include "DoEnemyProjectiles.h"
#include "Declarations.h"

#define XPOS		ProjectileVector.at(i)
#define YPOS		ProjectileVector.at(i + 2)
#define FRAME		ProjectileVector.at(i + 3)
#define FRAMETIME	ProjectileVector.at(i + 4)
#define ANGLE		ProjectileVector.at(i + 5)
#define XRATIO		ProjectileVector.at(i + 6)
#define YRATIO		ProjectileVector.at(i + 7)
#define ACTIVE		ProjectileVector.at(i + 8)

/*
Series for projectile vector
... xPos,yPos,Frame,Frametime,Angle,xRatio,yRatio,Active ... (8 variables)
	= x											  = x+7
*/

void DoEnemyProjectiles()
{
	for(int i = ProjectileVector.size() / 8; i < ProjectileVector.size();i+=8)
	{
		XPOS += XRATIO;
		YPOS += YRATIO;
		

	}