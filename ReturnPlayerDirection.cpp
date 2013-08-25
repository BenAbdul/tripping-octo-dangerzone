#include"ReturnPlayerDirection.h"
#include"Declarations.h"

/*
-1-2-3-
-4-5-6- This is what this function returns depending on where the mouse is on the screen
-7-8-9-
I know, I know
*/

int ReturnPlayerDirection(float MouseX, float MouseY)
{
	int Bad, Programming;

	if(MouseX < 267) Bad = 1;
	else if (MouseX < 534) Bad = 2;
	else Bad = 3;

	if(MouseY < 167) Programming = 1;
	else if (MouseY < 334) Programming = 2; //Y axis is inverted
	else Programming = 3;

	if(Bad == 1 && Programming == 1) return 1;
	else if(Bad == 1 && Programming == 2) return 4;
	else if(Bad == 1 && Programming == 3) return 7;
	else if(Bad == 2 && Programming == 1) return 2;
	else if(Bad == 2 && Programming == 2) return 5;
	else if(Bad == 2 && Programming == 3) return 8;
	else if(Bad == 3 && Programming == 1) return 3;
	else if(Bad == 3 && Programming == 2) return 6;
	else if(Bad == 3 && Programming == 3) return 9;
	else OpenDebugWindow("Something has gone awfuly wrong in ReturnPlayerDirection");
}