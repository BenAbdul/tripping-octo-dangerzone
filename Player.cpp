#include"Player.h"
#include"Declarations.h"
#include"CalculateProjectileAngle.h"

Player::Player()
{
	Lives = 3;
	Ammo = 0;
	CurrentSelection = 1; //Melee
	xVel = 0;
	yVel = 0;
	WorldxPos = 100;
	WorldyPos = 100;
	CurrentSprite = D1;
	xPos = (ScreenWidth - CurrentSprite->w)/2;
	yPos = (ScreenHeight - CurrentSprite->h)/2;
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
	xPos = (ScreenWidth - CurrentSprite->w)/2;
	yPos = (ScreenHeight - CurrentSprite->h)/2;

	if (WorldxPos < 500)
	{
		WorldxPos = 500;
		xVel = 0;
	}

	
	if (WorldxPos + CurrentSprite->w > Arena - 500)
	{
		WorldxPos = Arena - 500 - CurrentSprite->w;
		xVel = 0;
	}
	

	if (WorldyPos < 500)
	{
		WorldyPos = 500;
		yVel = 0;
	}

	
	if (WorldyPos + CurrentSprite->h > Arena - 500)
	{
		WorldyPos = Arena - 500 - CurrentSprite->h;
		yVel = 0;
	}
}

void Player::Fire()
{
	//I aint no magician
}