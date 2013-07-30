#include<math.h>

//Oh god no I hate trigonometry

int CalculateProjectileAngle(double PlayerX, double PlayerY, double MouseX, double MouseY)
{
	int Theta;
	if(PlayerX > MouseX && MouseY > PlayerY) Theta = 270 + (atan((MouseY - PlayerY) / (PlayerX - MouseX))); //If the mouse is to the top left of the player
	else if (MouseX > PlayerX && PlayerY > MouseY ) Theta = 180 - (atan((PlayerY - MouseY) / (MouseX - PlayerX))); //If the mouse is to the bottom right of the player
	else if (MouseX > PlayerX && MouseY > PlayerY) Theta = 90 - (atan((MouseY - PlayerY) / (MouseX - PlayerX))); //If the mouse is to the top right of the player
	else if (PlayerX > MouseX && PlayerY > MouseY) Theta = 270 - (atan((PlayerY - MouseY)/ (PlayerX - MouseX))); //If the mouse is to the bottom left of the player

	return Theta;
}