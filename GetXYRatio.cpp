#include "GetXYRatio.h"
#include "Declarations.h"

// Ratio/Gradient will be 1/-1:y

void GetXYRatio(int *xRatio, int *yRatio, int x, int y, int PlayerX, int PlayerY)
{
	y = 500 - y;
	PlayerY = 500 - y;

	if (x < PlayerX &&  y > PlayerY) //Top left
	{
		(*xRatio) = -1;
		(*yRatio) = y / (x * -1);
	}

	else if (x > PlayerX &&  y > PlayerY) //Top right
	{
		(*xRatio) = 1;
		(*yRatio) = y / x;
	}

	else if (x < PlayerX &&  y < PlayerY) //Bottom left
	{
		(*xRatio) = -1;
		(*yRatio) = (y * -1) / (x * -1);
	}

	else if (x > PlayerX &&  y < PlayerY) //Bottom right
	{
		(*xRatio) = 1;
		(*yRatio) = (y * -1) / x;
	}
}