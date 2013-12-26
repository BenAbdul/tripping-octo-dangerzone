#include<math.h>
#include"OpenDebugWindow.h"
#define PI 3.14159265

double CalculateProjectileAngle(float PlayerX, float PlayerY, float MouseX, float MouseY)
{
	float Theta, Calculation;
	PlayerY = 500 - PlayerY;
	MouseY = 500 - MouseY; //Y axis is inverted

	if((PlayerX > MouseX) && (MouseY > PlayerY))//If the mouse is to the top left of the player
	{
		Calculation = (MouseY - PlayerY) / (PlayerX - MouseX);
		Theta = atan(Calculation)* 180 / PI;
		return 270 + Theta;
	}

	else if ((MouseY > PlayerY) && (MouseX > PlayerX)) //If the mouse is to the top right of the player
	{
		Calculation = (MouseY - PlayerY) / (MouseX - PlayerX);
		Theta = atan(Calculation)* 180 / PI;
		return 90 - Theta;
	}

	else if ((PlayerX > MouseX) && (PlayerY > MouseY)) //If the mouse is to the bottom left of the player
	{
		Calculation = (PlayerX - MouseX) / (PlayerY - MouseY);
		Theta = atan(Calculation)* 180 / PI;
		return 180 + Theta;
	}

	else if ((MouseX > PlayerX) && (PlayerY > MouseY)) //If the mouse is to the bottom right of the player
	{
		Calculation = (MouseX - PlayerX) / (PlayerY - MouseY);
		Theta = atan(Calculation)* 180 / PI;
		return 180 - Theta;
	}
	else if (MouseX == PlayerX)
	{
		if (MouseY > PlayerY) return 0;
		else return 180;
	}
	else if (MouseY == PlayerY)
	{
		if(MouseX > PlayerX) return 90;
		else return 270;
	}
	else 
	{
		OpenDebugWindow("Something has gone wrong in CalculateProjectileAngle");
		return 999;
	}
}
