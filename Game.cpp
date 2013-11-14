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
#include<time.h>
#include<math.h>
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
	Timer Shot;
	Player Character;
	Camera Viewport;
	SDL_Surface *Weapon;
	bool Debug = true;
	int Temp;
	int FrameCount = 0;
	int EnemySpawnTimer = 120;
	double xRatio, yRatio = 0;
	bool ClickDone = false;
	bool PieceOfPoo = false;
	int YouDiedProgress = 0;
	double YouAreShitProgress = 0;
	PlayRandomMusic();
	Mix_Chunk *Minigun = NULL;
	Mix_Chunk *Machinegun= NULL;
	Mix_Chunk *Pistol= NULL;
	Mix_Chunk *Click= NULL;
	Minigun = Mix_LoadWAV("Resources/Sounds/Minigun.ogg");
	Machinegun = Mix_LoadWAV("Resources/Sounds/MachineGun.ogg");
	Pistol = Mix_LoadWAV("Resources/Sounds/Pistol.ogg");
	Click = Mix_LoadWAV("Resources/Sounds/Fail.ogg");
	while (Quit == false && State == GAME)
	{
		FPS.start();
		if (Ded == true)
		{
			if (YouDiedProgress < 90) YouDiedProgress ++;
			if (YouDiedProgress > 45 && YouAreShitProgress < 92 && ClickDone == false) YouAreShitProgress++;

			for(int x = 0; x < EnemyVector.size(); x++)
			{
				if (KillerID == EnemyVector.at(x).ID) Viewport.MoveCameraTo(EnemyVector.at(x).xPos - (ScreenWidth - 49)/2 , EnemyVector.at(x).yPos - (ScreenHeight - Character.CurrentSprite->h)/2);
			}
		}

		FrameCount++;
		if(FrameCount == EnemySpawnTimer)
		{
			FrameCount = 0;
			if (EnemySpawnTimer > 30) EnemySpawnTimer-=2;
			CreateEnemy();
		}
		Character.HandleEvents();
		Character.UpdatePosition();
		PlayerX = Character.WorldxPos;
		PlayerY = Character.WorldyPos;
		int PlayerDirection = ReturnPlayerDirection(Mouse.MouseX,Mouse.MouseY);
		
		if(Ded == false)
		{
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
		}

		XChange = 0;
		YChange = 0;
		int LAYZX = -300;
		int LAYZX2 = 1100;

		if(Mouse.MouseX > 700) 
		{
			Viewport.CameraRect.x += (Mouse.MouseX - 700) *1.2;
		}

		else if(Mouse.MouseX < 100) 
		{
			Viewport.CameraRect.x -= (100 - Mouse.MouseX)* 1.2;
		}

		if(Mouse.MouseY > 400) 
		{
			Viewport.CameraRect.y += (Mouse.MouseY - 400)* 1.2;
		}

		else if(Mouse.MouseY < 100) 
		{
			Viewport.CameraRect.y -= (100 - Mouse.MouseY)* 1.5;
		}
		CameraX = Viewport.CameraRect.x;
		CameraY = Viewport.CameraRect.y;

		if (MouseDown == true && Shot.get_ticks() > 200 && Ded == false)
		{
				ProjectileVector.push_back(Character.WorldxPos);
				ProjectileVector.push_back(Character.WorldyPos);
				ProjectileVector.push_back(0);
				ProjectileVector.push_back(0);
				int Spray = (rand () % 8 + 1) - 4;
				if (xRatio > 0)ProjectileVector.push_back(xRatio + Spray + (Character.xVel / 2));
				else ProjectileVector.push_back(xRatio - Spray + (Character.xVel / 2));
				ProjectileVector.push_back((yRatio * -1)+ Character.yVel);
				ProjectileVector.push_back(1);
				SpareStream.str("");
				SpareStream << "Projectile created with ratio X += " << xRatio << " Y += " << yRatio << ". The projectile was created at (" << Character.WorldxPos << "," << Character.WorldyPos << ")";
				OpenDebugWindow(SpareStream.str());
				Shot.start();
		}
		if(Shot.get_ticks() > 6000) ProjectileVector.erase(ProjectileVector.begin(),ProjectileVector.end());
		ApplySurface(0,0,Background,Screen,&Viewport.CameraRect);
		ApplySurface(Character.WorldxPos - Viewport.CameraRect.x,Character.WorldyPos - Viewport.CameraRect.y,Character.CurrentSprite,Screen);
		Mouse.Render();
		DoEnemies();
		DoEnemyProjectiles();
		if (Ded == false)
		{
			Weapon = rotozoomSurface(Sniper,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
			ApplySurface((Character.WorldxPos - Viewport.CameraRect.x) - 50,(Character.WorldyPos - Viewport.CameraRect.y) - 50,Weapon,Screen);
		}
		else
		{
			Debug = false;
			double HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING = YouDiedProgress * (PI / 180);
			double HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING_THE_RETURN = YouDiedProgress * (PI / 180);
			int x = 330 * (sin(HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING));
			LAYZX += x;
			ApplySurface(LAYZX,50,YouDied,Screen);
			x = 800 * (sin(HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING_THE_RETURN));
			LAYZX2 -= x;
			ApplySurface(LAYZX2,150,YouAreShit,Screen);
		}
		if (YouAreShitProgress == 91)
			{
				YouAreShitProgress--;
				if(ClickDone == false)
				{
					if (Kills < 5) Mix_PlayChannel(-1,Click,0);
					else if (Kills < 30) Mix_PlayChannel(-1,Pistol,0);
					else if (Kills < 60) Mix_PlayChannel(-1,Machinegun,0);
					else if (Kills < 100) Mix_PlayChannel(-1,Minigun,0);
					ApplySurface((ScreenWidth - KillsImg->w) / 2,250,KillsImg,Screen);
					ClickDone = true;
					PieceOfPoo = true;
				}
			}
		if (PieceOfPoo == true) ApplySurface((ScreenWidth - KillsImg->w) / 2,250,KillsImg,Screen);
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
			DebugStream << "Kills: " << Kills;
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,150,Message2,Screen);
			DebugStream.str("");
			if(LDown == true) DebugStream << " Left ";
			if(RDown == true) DebugStream << " Right";
			if(UDown == true) DebugStream << " Up ";
			if(DDown == true) DebugStream << " Down ";
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,175,Message2,Screen);
			if (Ded == true)
			{
			DebugStream.str("");
			DebugStream << "Ded";
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,200,Message2,Screen);
			}
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

			if(event.type == SDL_MOUSEBUTTONDOWN && Ded == false) 
			{
				ProjectileVector.push_back(Character.WorldxPos);
				ProjectileVector.push_back(Character.WorldyPos);
				ProjectileVector.push_back(0);
				ProjectileVector.push_back(0);
				srand(time(NULL));
				int Spray = (rand () % 8 + 1) - 4;
				if (xRatio > 0)ProjectileVector.push_back(xRatio + Spray + Character.xVel);
				else ProjectileVector.push_back(xRatio - Spray + Character.xVel);
				ProjectileVector.push_back((yRatio * -1)+ Character.yVel);
				ProjectileVector.push_back(1);
				SpareStream.str("");
				SpareStream << "Projectile created with ratio X += " << xRatio << " Y += " << yRatio << ". The projectile was created at (" << Character.WorldxPos << "," << Character.WorldyPos << ")";
				OpenDebugWindow(SpareStream.str());
				
				MouseDown = true;
				OpenDebugWindow("Shots fired!");
				Shot.start();
			}
			if(event.type == SDL_MOUSEBUTTONUP) MouseDown = false;
			if (event.type == SDL_KEYDOWN)
			{
				if (Ded == false)
				{
					if(event.key.keysym.sym == SDLK_LEFT) LDown = true;
					if(event.key.keysym.sym == SDLK_RIGHT) RDown = true;
					if(event.key.keysym.sym == SDLK_UP) UDown = true;
					if(event.key.keysym.sym == SDLK_DOWN) DDown = true;
				}

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

				if(event.key.keysym.sym == SDLK_f && Debug == true)
				{
					LazyDebug = true;
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
				if(event.key.keysym.sym == SDLK_f) LazyDebug = false;
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