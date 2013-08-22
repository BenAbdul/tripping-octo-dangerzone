#include"Declarations.h"
#include"Timer.h"
#include"Player.h"
#include"Game.h"
#include"Camera.h"
#include"Cursor.h"
#include"PlayRandomMusic.h"
#include"CalculateProjectileAngle.h"
#include"Pause.h"
#include"OpenDebugWindow.h"
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
	bool Debug = false;
	int Temp;
	PlayRandomMusic();
	while (Quit == false && State == GAME)
	{
		FPS.start();		
		Character.HandleEvents();
		Character.UpdatePosition();

		if(Mouse.MouseX > 700) 
		{
			Viewport.CameraRect.x += (Mouse.MouseX - 700) *1.2;
			Character.xPos -= (Mouse.MouseX - 700)*1.2;
		}

		if(Mouse.MouseX < 100) 
		{
			Viewport.CameraRect.x -= (100 - Mouse.MouseX)* 1.2;
			Character.xPos += (100 - Mouse.MouseX)* 1.2;
		}

		if(Mouse.MouseY > 400) 
		{
			Viewport.CameraRect.y += (Mouse.MouseY - 400)* 1.2;
			Character.yPos -= (Mouse.MouseY - 400)* 1.2;
		}

		if(Mouse.MouseY < 100) 
		{
			Viewport.CameraRect.y -= (100 - Mouse.MouseY)* 1.5;
			Character.yPos += (100 - Mouse.MouseY) * 1.5;
		}

		ApplySurface(0,0,Background,Screen,&Viewport.CameraRect);
		ApplySurface(Character.xPos, Character.yPos, Character1, Screen);
		Mouse.Render();
		if(Debug = true)
		{
			std::stringstream DebugStream;
			DebugStream.str("");
			DebugStream << "Character world position " << Character.WorldxPos << " - " << Character.WorldyPos;
			Message1 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,0,Message1,Screen);
			DebugStream.str("");
			DebugStream << "Character screen position " << Character.xPos << " - " << Character.yPos;
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
			DebugStream << "Current Angle " << CalculateProjectileAngle(Character.xPos,Character.yPos,Mouse.MouseX,Mouse.MouseY); //(int PlayerX, int PlayerY, int MouseX, int MouseY)
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,100,Message2,Screen);
			DebugStream.str("");
			if(LDown == true) DebugStream << " Left ";
			if(RDown == true) DebugStream << " Right";
			if(UDown == true) DebugStream << " Up ";
			if(DDown == true) DebugStream << " Down ";
			Message2 = TTF_RenderText_Solid(EightBitLimitSmall,DebugStream.str().c_str(),White);
			ApplySurface(0,125,Message2,Screen);
		}
		Viewport.MoveCameraTo(Character.WorldxPos - (ScreenWidth - Character1->w)/2 , Character.WorldyPos - (ScreenHeight - Character1->h)/2);
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

			if(event.type == SDL_MOUSEMOTION)
			{
				Mouse.MouseX = event.motion.x;
				Mouse.MouseY = event.motion.y;
			}
		}
		if (FPS.get_ticks() < 1000 / 60) SDL_Delay(1000/60 - FPS.get_ticks());
	}
}