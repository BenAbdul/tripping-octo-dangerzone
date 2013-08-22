#include<math.h>

//Oh god no I hate trigonometry

double CalculateProjectileAngle(double PlayerX, double PlayerY, double MouseX, double MouseY)
{
	int Theta = 0;
	if(PlayerX > MouseX && MouseY > PlayerY) Theta = (atan((MouseY - PlayerY) / (PlayerX - MouseX))); //If the mouse is to the top left of the player, 270 +
	else if (MouseX > PlayerX && PlayerY > MouseY ) Theta = (atan((PlayerY - MouseY) / (MouseX - PlayerX))); //If the mouse is to the bottom right of the player 180 - 
	else if (MouseX > PlayerX && MouseY > PlayerY) Theta =  (atan((MouseY - PlayerY) / (MouseX - PlayerX))); //If the mouse is to the top right of the player 90 -
	else if (PlayerX > MouseX && PlayerY > MouseY) Theta =  (atan((PlayerY - MouseY)/ (PlayerX - MouseX))); //If the mouse is to the bottom left of the player 270 -
	else if (MouseX == PlayerX)
	{
		if (MouseY > PlayerY) Theta = 0;
		else Theta = 180;
	}
	else if (MouseY = PlayerY)
	{
		if(MouseX > PlayerX) Theta = 90;
		else Theta = 270;
	}
	return Theta;
}