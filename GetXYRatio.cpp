#include "GetXYRatio.h"
#include "Declarations.h"


void GetXYRatio(double *xRatio, double *yRatio, double x, double y, double PlayerX, double PlayerY)
{
	y = 500 - y;
	PlayerY = 486 - PlayerY;
	PlayerX = PlayerX + 15;
	double DeltaX, DeltaY;
	double Distance;

	if (x < PlayerX &&  y > PlayerY) //Top left
	{
		DeltaX = PlayerX - x;
		DeltaY = y - PlayerY;
		Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
		(*xRatio) = (DeltaX *-10) / Distance;
		(*yRatio) = DeltaY * 10 / Distance;
	}

	else if (x > PlayerX &&  y > PlayerY) //Top right
	{
		DeltaX = x - PlayerX;
		DeltaY = y - PlayerY;
		Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
		(*xRatio) = DeltaX * 10 / Distance;
		(*yRatio) = DeltaY * 10 / Distance;
	}

	else if (x < PlayerX &&  y < PlayerY) //Bottom left
	{
		DeltaX = PlayerX - x;
		DeltaY = PlayerY - y;
		Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
		(*xRatio) = (DeltaX * -10) / Distance;
		(*yRatio) = (DeltaY * -10) / Distance;
	}

	else if (x > PlayerX &&  y < PlayerY) //Bottom right
	{
		DeltaX = x - PlayerX;
		DeltaY = PlayerY - y;
		Distance = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
		(*xRatio) = DeltaX * 10 / Distance;
		(*yRatio) = (DeltaY * -10) / Distance;
	}
}