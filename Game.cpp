#define PI 3.14159265359

#include"Declarations.h"
#include"Timer.h"
#include"Player.h"
#include"Game.h"
#include"Camera.h"
#include"Cursor.h"
#include"PlayRandomMusic.h"
#include"CalculateProjectileAngle.h"
#include"ReturnPlayerDirection.h"
#include"Pause.h"
#include"DoEnemies.h"
#include"OpenDebugWindow.h"
#include"DoEnemyProjectiles.h"
#include"GetXYRatio.h"
#include<SDL_rotozoom.h>
#include<math.h>
#include<windows.h>
#include<sstream>

void Game()
{
	SDL_WM_GrabInput( SDL_GRAB_ON );
	SDL_ShowCursor(SDL_DISABLE);
	Cursor Mouse;
	SpareStream.str("");
	SpareStream << "At the time of declaration, Mouse.FrameTime is " << Mouse.FrameTime;
	OpenDebugWindow(SpareStream.str());
	Timer FPS;
	Player Character;
	Camera Viewport;
	SDL_Surface *Weapon;
	bool Debug = false;
	int Temp;
	double xRatio, yRatio = 0;
	PlayRandomMusic();
	while (Quit == false && State == GAME)
	{
		FPS.start();
		PlayerX = Character.WorldxPos;
		PlayerY = Character.WorldyPos; // le lazy interface
		Character.HandleEvents();
		Character.UpdatePosition();
		CameraX = Viewport.CameraRect.x;
		CameraY = Viewport.CameraRect.y;
		int PlayerDirection = ReturnPlayerDirection(Mouse.MouseX,Mouse.MouseY);
		switch(PlayerDirection)
		{
		case 1:
		case 2:
		case 3: Character.CurrentSprite = U1; break;
		case 4: Character.CurrentSprite = L1; break;
		case 5:
			if (Mouse.MouseY > 250) Character.CurrentSprite = D1;
			else Character.CurrentSprite = U1;
			break;
		case 6: Character.CurrentSprite = R1;break;
		case 7:
		case 8:
		case 9: Character.CurrentSprite = D1; break;
		}

		XChange = 0;
		YChange = 0;

		if(Mouse.MouseX > 700) 
		{
			Viewport.CameraRect.x += (Mouse.MouseX - 700) *1.2;
		}

		else if(Mouse.MouseX < 100) 
		{
			Viewport.CameraRect.x -= (100 - Mouse.MouseX)* 1.2;
		}

		else if(Mouse.MouseY > 400) 
		{
			Viewport.CameraRect.y += (Mouse.MouseY - 400)* 1.2;
		}

		else if(Mouse.MouseY < 100) 
		{
			Viewport.CameraRect.y -= (100 - Mouse.MouseY)* 1.5;
		}

		ApplySurface(0,0,Background,Screen,&Viewport.CameraRect);
		ApplySurface(Character.WorldxPos - Viewport.CameraRect.x,Character.WorldyPos - Viewport.CameraRect.y,Character.CurrentSprite,Screen);
		Weapon = rotozoomSurface(Sniper,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
		ApplySurface((Character.WorldxPos - Viewport.CameraRect.x) - 50,(Character.WorldyPos - Viewport.CameraRect.y) - 50,Weapon,Screen);
		Mouse.Render();
		DoEnemies();
		DoEnemyProjectiles();
		ApplySurface(0,500 - HUD->h,HUD,Screen);
		if(Debug == true)
		{
			std::stringstream DebugStream;
			DebugStream.str("");
			DebugStream << "Character world position " << Character.WorldxPos << " - " << Character.WorldyPos;
			Message1 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,0,Message1,Screen);
			DebugStream.str("");
			DebugStream << "Character screen position " << Character.WorldxPos - Viewport.CameraRect.x << " - " << Character.WorldyPos - Viewport.CameraRect.y;
			Message1 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,25,Message1,Screen);
			DebugStream.str("");
			DebugStream << "Cursor position " << Mouse.MouseX << " - " << Mouse.MouseY;
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,50,Message2,Screen);
			DebugStream.str("");
			DebugStream << "Camera position " << Viewport.CameraRect.x << " - " << Viewport.CameraRect.y;
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,75,Message2,Screen);
			DebugStream.str("");
			DebugStream << "Current Angle " << CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY); //(int PlayerX, int PlayerY, int MouseX, int MouseY)
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,100,Message2,Screen);
			DebugStream.str("");
		    GetXYRatio(&xRatio,&yRatio,Mouse.MouseX,Mouse.MouseY,Character.WorldxPos - Viewport.CameraRect.x,Character.WorldyPos - Viewport.CameraRect.y);
			DebugStream << "Current X to Y ratio " << xRatio << " - " << yRatio;
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,125,Message2,Screen);
			DebugStream.str("");
			DebugStream << "Press n for a juicy debug log";
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,150,Message2,Screen);
			DebugStream.str("");
			if(LDown == true) DebugStream << " Left ";
			if(RDown == true) DebugStream << " Right";
			if(UDown == true) DebugStream << " Up ";
			if(DDown == true) DebugStream << " Down ";
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,175,Message2,Screen);
		}
		Viewport.MoveCameraTo(Character.WorldxPos - (ScreenWidth - Character.CurrentSprite->w)/2 , Character.WorldyPos - (ScreenHeight - Character.CurrentSprite->h)/2);
		SDL_Flip(Screen);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				Quit = true;
				State = MENU;
			}

			if (event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_LEFT) LDown = true;
				if(event.key.keysym.sym == SDLK_RIGHT) RDown = true;
				if(event.key.keysym.sym == SDLK_UP) UDown = true;
				if(event.key.keysym.sym == SDLK_DOWN) DDown = true;

				if(event.key.keysym.sym == SDLK_TAB) Debug = !Debug;

				if(event.key.keysym.sym == SDLK_n && Debug == true)
				{
					OpenDebugWindow("Open");
					Pause();
				}

				if(event.key.keysym.sym == SDLK_e && Debug == true)
				{
					CreateEnemy();
				}

				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					Pause();
				}
			}

			if(event.type == SDL_KEYUP)
			{
				if(event.key.keysym.sym == SDLK_LEFT) LDown = false;
				if(event.key.keysym.sym == SDLK_RIGHT) RDown = false;
				if(event.key.keysym.sym == SDLK_UP) UDown = false;
				if(event.key.keysym.sym == SDLK_DOWN) DDown = false;
			}

			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				/*
				Series for projectile vector
			... xPos,yPos,Frame,Frametime,xRatio,yRatio,Active ... (7 variables)
				= x										 = x+6
				*/
				
				ProjectileVector.push_back(Character.WorldxPos);
				ProjectileVector.push_back(Character.WorldyPos);
				ProjectileVector.push_back(0);
				ProjectileVector.push_back(0);
				ProjectileVector.push_back(xRatio);
				ProjectileVector.push_back(yRatio * -1);
				ProjectileVector.push_back(1);
				SpareStream.str("");
				SpareStream << "Projectile created with ratio y += " << -1 << ". The projectile was created at (" << Character.WorldxPos << "," << Character.WorldyPos << ")";
				OpenDebugWindow(SpareStream.str());
			}

			if(event.type == SDL_MOUSEMOTION)
			{
				Mouse.MouseX = event.motion.x;
				Mouse.MouseY = event.motion.y;
			}
		}
		if (FPS.get_ticks() < 1000 / 60) SDL_Delay(1000/60 - FPS.get_ticks());
	}
}