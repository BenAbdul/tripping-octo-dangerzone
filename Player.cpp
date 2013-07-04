#include"Player.h"
#include"Declarations.h"

Player::Player()
{
	Lives = 3;
	Ammo = 0;
	CurrentSelection = 1; //Melee
	xVel = 0;
	yVel = 0;
	xPos = 400;
	yPos = 250;
}

void Player::HandleEvents()
{
	if (ArrowStates[SDLK_LEFT])
	{
		if (xVel - 5 < -20) xVel = -20;
		else xVel -=5;
	}

	if (ArrowStates[SDLK_RIGHT])
	{
		if (xVel + 5 > 20) xVel = 20;
		else xVel += 5;
	}

	if (ArrowStates[SDLK_UP])
	{
		if (yVel - 5 < -20) yVel = -20;
		else yVel -= 5;
	}

	if (ArrowStates[SDLK_DOWN])
	{
		if (yVel + 5 > 20) yVel = 20;
		else yVel += 5;
	}

	if (ArrowStates[SDLK_UP] == false && ArrowStates[SDLK_DOWN] == false 
		&& ArrowStates[SDLK_LEFT] == false && ArrowStates[SDLK_RIGHT] == false)
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

void Player::Render()
{
	ApplySurface(xPos, yPos, Character, Screen);
}

void Player::UpdatePosition()
{
	xPos += xVel;
	yPos += yVel;
}

void Player::Fire()
{
	//nigga I aint no magician
}