#include "GetXYRatio.h"
#include "Declarations.h"


void GetXYRatio(double *xRatio, double *yRatio, double x, double y, double PlayerX, double PlayerY)
{
	y = 500 - y;
	PlayerY = 500 - y;
	double DeltaX, DeltaY;
	double Distance;

	if (x < PlayerX &&  y > PlayerY) //Top left
	{
		DeltaX = PlayerX - x;
		DeltaY = y - PlayerY;
		Distance = sqrt(DeltaX + DeltaY);
		(*xRatio) = (DeltaX *-1) / Distance;
		(*yRatio) = DeltaY / Distance;
	}

	else if (x > PlayerX &&  y > PlayerY) //Top right
	{
		DeltaX = x - PlayerX;
		DeltaY = y - PlayerY;
		Distance = sqrt(DeltaX + DeltaY);
		(*xRatio) = DeltaX / Distance;
		(*yRatio) = DeltaY / Distance;
	}

	else if (x < PlayerX &&  y < PlayerY) //Bottom left
	{
		DeltaX = PlayerX - x;
		DeltaY = PlayerY - y;
		Distance = sqrt(DeltaX + DeltaY);
		(*xRatio) = (DeltaX * -1) / Distance;
		(*yRatio) = (DeltaY * -1) / Distance;
	}

	else if (x > PlayerX &&  y < PlayerY) //Bottom right
	{
		DeltaX = x - PlayerX;
		DeltaY = PlayerY - y;
		Distance = sqrt(DeltaX + DeltaY);
		(*xRatio) = DeltaX / Distance;
		(*yRatio) = (DeltaY * -1) / Distance;
	}
}