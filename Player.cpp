#include"Player.h"
#include"Declarations.h"

Player::Player()
{
	Lives = 3;
	Ammo = 0;
	CurrentSelection = 1; //Melee
	xVel = 0;
	yVel = 0;
	WorldxPos = 100;
	WorldyPos = 100;
	xPos = (ScreenWidth - Character1->w)/2;
	yPos = (ScreenHeight - Character1->h)/2;
}

void Player::HandleEvents()
{
	if (LDown == true)
	{
		if (xVel - 1 < -20) xVel = -10;
		else xVel -=1;
	}

	if (RDown == true)
	{
		if (xVel + 1 > 20) xVel = 10;
		else xVel += 1;
	}

	if (UDown == true)
	{
		if (yVel - 1 < -20) yVel = -10;
		else yVel -= 1;
	}

	if (DDown == true)
	{
		if (yVel + 1 > 20) yVel = 10;
		else yVel += 1;
	}

	if (UDown == false && DDown == false &&  LDown == false && RDown == false)
	{
		if (yVel != 0)
		{
			if (yVel > 0)
			{
				if (yVel - 3 < 0) yVel = 0;
				else yVel -= 3;
			}

			if (yVel < 0)
			{
				if (yVel + 3 > 0) yVel = 0;
				else yVel += 3;
			}
		}

		if (xVel != 0)
		{
			if (xVel > 0)
			{
				if (xVel - 3 < 0) xVel = 0;
				else xVel -= 3;
			}

			if (xVel < 0)
			{
				if (xVel + 3 > 0) xVel = 0;
				else xVel += 3;
			}
		}
	}
}

void Player::UpdatePosition()
{
	WorldxPos += xVel;
	WorldyPos += yVel;
	xPos = (ScreenWidth - Character1->w)/2;
	yPos = (ScreenHeight - Character1->h)/2;

	if (WorldxPos < 500)
	{
		WorldxPos = 500;
		xVel = 0;
	}

	
	if (WorldxPos + Character1->w > 1500)
	{
		WorldxPos = 1500 - Character1->w;
		xVel = 0;
	}
	

	if (WorldyPos < 500)
	{
		WorldyPos = 500;
		yVel = 0;
	}

	
	if (WorldyPos + Character1->h > 1500)
	{
		WorldyPos = 1500 - Character1->h;
		yVel = 0;
	}
	
	/*
	if (xPos < 100)
	{
		xPos = 100;
	}

	if (xPos + Character1->w > 700)
	{
		xPos = (700 - Character1->w);
	}

	if (yPos < 100) 
	{
		yPos = 100;
	}

	if (yPos + Character1->h > 400)
	{
		yPos = 400 - (Character1->h);
	}
	*/
}

void Player::Fire()
{
	//I aint no magician
}