#define PI 3.14159265359

#include"Declarations.h"
#include"Timer.h"
#include"Player.h"
#include"Game.h"
#include"Camera.h"
#include"Cursor.h"
#include"CalculateProjectileAngle.h"
#include"ReturnPlayerDirection.h"
#include"Pause.h"
#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#include"DoEnemies.h"
#include"OpenDebugWindow.h"
#include"DoEnemyProjectiles.h"
#include"GetXYRatio.h"
#include<SDL_rotozoom.h>
#include<math.h>
#include<windows.h>
#include<fstream>
#include<sstream>

Player Character;
Camera Viewport;


#define UNICODEINPUT event.key.keysym.unicode
std::string GetStringInput()
{
	bool Done = false;	
	std::string ReturnThis = "NotBad";
	Message1 = TTF_RenderText_Solid(Takara,"Enter your name:",White);
	Message2 = TTF_RenderText_Solid(TakaraBig,"You made the high scores!",White);
	SDL_Surface * CurrentInput = TTF_RenderText_Solid(EightBitLimitBig,ReturnThis.c_str(),White);
	SDL_EnableUNICODE(SDL_ENABLE);
	while (!Done)
	{
		ApplySurface(0,0,Background,Screen);
		ApplySurface((ScreenWidth - Message1->w)/2,190,Message1,Screen);
		ApplySurface((ScreenWidth - Message2->w)/2,50,Message2,Screen);
		CurrentInput = TTF_RenderText_Solid(EightBitLimitBig,ReturnThis.c_str(),White);
		ApplySurface((ScreenWidth - CurrentInput->w)/2, (ScreenHeight - CurrentInput->h) /2, CurrentInput,Screen); 
		SDL_Flip(Screen);
		SDL_PumpEvents();
		while(SDL_PollEvent(&event));
		{
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) 
				Done = true;
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
			{
				if(ReturnThis.size() == 1) ReturnThis = " ";
				else ReturnThis.erase(ReturnThis.size()-1,1);
				SDL_Delay(150);
			}
			else if (ReturnThis.size() < 11)
			{
				if (UNICODEINPUT >= (Uint16)'A' && UNICODEINPUT <= (Uint16)'Z')
				{
					if (ReturnThis == " ") ReturnThis = ""; //bow down before me
					ReturnThis += UNICODEINPUT; 
					SDL_Delay(150);
				}
				
				else if (UNICODEINPUT >= (Uint16)'a' && UNICODEINPUT <= (Uint16)'z')
				{
					if (ReturnThis == " ") ReturnThis = "";
					ReturnThis += UNICODEINPUT; 
					SDL_Delay(150);
				}
			}
		}
	}
	return ReturnThis;
}

std::vector <int> BubbleSortVector(std::vector <int> ScoresVector)
{
	bool Done = false;
	OpenDebugWindow("Entering BubbleSortVector");
	while (Done == false)
	{
		Done = true;
		OpenDebugWindow("ScoresVector:");
		SpareStream.str("");
		for (int i = 0; i < 4; i++) SpareStream << ScoresVector.at(i) << " ";
		OpenDebugWindow(SpareStream.str().c_str());
		OpenDebugWindow("ICantCode:");
		SpareStream.str("");
		for (int i = 0; i < 4; i++) SpareStream << ICantCode.at(i) << " ";
		OpenDebugWindow(SpareStream.str().c_str());
		
		for (int i = 0; i < ScoresVector.size() - 1; i++)
		{
			if(ScoresVector.at(i) < ScoresVector.at(i+1))
			{
				int Temp = ScoresVector.at(i+1);
				ScoresVector.at(i+1) = ScoresVector.at(i);
				ScoresVector.at(i) = Temp;

				Temp = ICantCode.at(i+1);
				ICantCode.at(i+1) = ICantCode.at(i);
				ICantCode.at(i) = Temp;

				Done = false;
			}
		}
	}
	return ScoresVector;
}

void Game()
{
	SDL_WM_GrabInput( SDL_GRAB_ON );
	SDL_ShowCursor(SDL_DISABLE);
	ICantCode.erase(ICantCode.begin(),ICantCode.end());
	for (int i = 0; i <= 3; i++) ICantCode.push_back(i);
	Cursor Mouse;
	SpareStream.str("");
	SpareStream << "At the time of declaration, Mouse.FrameTime is " << Mouse.FrameTime;
	OpenDebugWindow(SpareStream.str());
	Timer FPS;
	int LAYZX3 = 500 - HUD->h;
	Timer Shot;
	SDL_Surface *Weapon;
	SDL_Surface *Message;
	SDL_Rect Big;
	double Counter = 0;
	Big.h = 500;
	Big.w = 800;
	SDL_Rect Small;
	Small.h = 500;
	Small.w = 800;
	bool Debug = false;
	int Temp;
	int FrameCount = 0;
	int SomeOtherCount = 0;
	int EnemySpawnTimer = 0;
	double xRatio, yRatio = 0;
	bool ClickDone = false;
	bool PieceOfPoo = false;
	bool ScoresDone = false;
	int YouDiedProgress = 0;
	double StartProgress = 0;
	double YouAreShitProgress = 0;
	Mix_Chunk *WickedSick = NULL;
	Mix_Chunk *Minigun = NULL;
	Mix_Chunk *Machinegun= NULL;
	Mix_Chunk *Pistol= NULL;
	Mix_Chunk *Click= NULL;
	WickedSick = Mix_LoadWAV("Resources/Sounds/WickedSick.ogg");
	Minigun = Mix_LoadWAV("Resources/Sounds/Minigun.ogg");
	Machinegun = Mix_LoadWAV("Resources/Sounds/MachineGun.ogg");
	Pistol = Mix_LoadWAV("Resources/Sounds/Pistol.ogg");
	Click = Mix_LoadWAV("Resources/Sounds/Fail.ogg");
	while (Quit == false && State == GAME)
	{
		FPS.start();

		CheckShake();
		LazyFlag2 = false;

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
		if(FrameCount == 90)
		{
			FrameCount = 0;
			SomeOtherCount++;
			if (SomeOtherCount == 4 && EnemySpawnTimer < 4) EnemySpawnTimer++; 
			LazyFlag2 = false;
			for (int x = EnemySpawnTimer; x >= 0; x--) CreateEnemy();
		}

		Character.HandleEvents();
		Character.UpdatePosition();
		PlayerX = Character.WorldxPos;
		PlayerY = Character.WorldyPos;
		PlayerXVel = Character.xVel;
		PlayerYVel = Character.yVel;
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
				int Spray = (rand () % 6 + 1) - 3;
				if (xRatio > 0)ProjectileVector.push_back(xRatio + Spray + (Character.xVel / 2));
				else ProjectileVector.push_back(xRatio - Spray + (Character.xVel / 2));
				ProjectileVector.push_back((yRatio * -1)+ Character.yVel);
				ProjectileVector.push_back(1);
				Shot.start();
		}

		if(Shot.get_ticks() > 6000) ProjectileVector.erase(ProjectileVector.begin(),ProjectileVector.end());
		Viewport.CameraRect.x -= 500;
		Viewport.CameraRect.y -= 500;
		ApplySurface(0,0,Background,Screen,&Viewport.CameraRect);
		Viewport.CameraRect.x += 500;
		Viewport.CameraRect.y += 500;
		Big.x = CameraX / 10;
		Big.y = CameraY / 10;
		Small.x = CameraX / 30;
		Small.y = CameraY / 30;
		ApplySurface(0,0,SmallGrid,Screen,&Small);
		ApplySurface(0,0,BigGrid,Screen,&Big);
		if (Viewport.CameraRect.x < 500 || Viewport.CameraRect.x > 4200) ApplySurface(0,0,Background2,Screen,&Viewport.CameraRect);
		else if (Viewport.CameraRect.y < 500 || Viewport.CameraRect.y > 4500) ApplySurface(0,0,Background2,Screen,&Viewport.CameraRect);
		if (ShallIRenderHim == true) ApplySurface(Character.WorldxPos - Viewport.CameraRect.x,Character.WorldyPos - Viewport.CameraRect.y,Character.CurrentSprite,Screen);
		Mouse.Render();
		DoEnemyProjectiles();

		if (Ded == false)
		{
			ApplySurface(0,500 - HUD->h,HUD,Screen);
			if (PlayerDirection == 1 || PlayerDirection == 7 || PlayerDirection == 4) Weapon = rotozoomSurface(SniperFlipped,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
			else if (PlayerDirection == 5)
			{
				if (Mouse.MouseX < ScreenWidth / 2) Weapon = rotozoomSurface(SniperFlipped,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
				else Weapon = rotozoomSurface(Sniper,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
			}
			else Weapon = rotozoomSurface(Sniper,360 - CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY),1,0);
			int ExOffSet = (Sniper->w / 2) - Weapon->w / 2;
			int WhyOffSet = (Sniper->h / 2) - Weapon->h / 2;
			ApplySurface((Character.WorldxPos - Viewport.CameraRect.x + ExOffSet + Character.CurrentSprite->w/2) - 49,(Character.WorldyPos - Viewport.CameraRect.y + WhyOffSet + Character.CurrentSprite->h/2) - 49,Weapon,Screen);
			int tni = 0; //int backwards 8^)
			for (tni = 0; tni <= Lives; tni++) 
			{
				//__debugbreak();
				ApplySurface(56 + (45 * tni),(500 - HUD->h) + 20,LivesIcon,Screen);
			}

			SpareStream.str("");
			SpareStream << Kills;
			std::string KillsString = SpareStream.str();

			for (int i = 0; i <= 4; i++)
			{
				if(i < KillsString.size()) 
				{
					std::string Cheat = KillsString.substr(i,1);
					const char *KillsChar = Cheat.c_str();
					Message = TTF_RenderText_Solid(EightBitLimit,KillsChar,White);
				}
				else Message = TTF_RenderText_Solid(EightBitLimit,"-",White);
				ApplySurface(540 + (45 * i),(500 - HUD->h) + 21,Message,Screen);
			}
		}
		
		else
		{
			Debug = false;
			double HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING = YouDiedProgress * (PI / 180);
			double HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING_THE_RETURN = YouDiedProgress * (PI / 180);
			int x = 330 * (sin(HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING));
			LAYZX += x;
			ApplySurface(LAYZX,40,YouDied,Screen);
			x = 800 * (sin(HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING_THE_RETURN));
			LAYZX2 -= x; 
			ApplySurface(LAYZX2,140,YouAreShit,Screen);
			x = 3 * (sin(HURR_SIN_WONT_TAKE_AN_INT_AND_THIS_IS_EASIER_THAN_GOOGLING_THE_RETURN));
			LAYZX3 += x;  //actually should be LAYZY but I'm feeling layz
			ApplySurface(0,LAYZX3,HUD,Screen);


			SpareStream.str("");
			SpareStream << Kills;
			std::string KillsString = SpareStream.str();

			for (int i = 0; i <= 4; i++)
			{
				if(i < KillsString.size()) 
				{
					std::string Cheat = KillsString.substr(i,i+1);
					const char *KillsChar = Cheat.c_str();
					Message = TTF_RenderText_Solid(EightBitLimit,KillsChar,White);
				} 
				else Message = TTF_RenderText_Solid(EightBitLimit,"-",White); 
				ApplySurface(540 + (45 * i),LAYZX3 + 24,Message,Screen); 
			} 
		} 
		 
		DoEnemies(); 
		 
		if (YouAreShitProgress == 91)
		{

			YouAreShitProgress--;
			if(ClickDone == false)
			{
				if (PlsPlaySound == true)
				{
					if (Kills < 25) Mix_PlayChannel(-1,Click,0);
					else if (Kills < 100) Mix_PlayChannel(-1,Pistol,0);
					else if (Kills < 150) Mix_PlayChannel(-1,Machinegun,0);
					else if (Kills < 200) Mix_PlayChannel(-1,Minigun,0);
					else {Mix_PlayChannel(-1,WickedSick,0); Mix_HaltMusic();}
				}

				ApplySurface((ScreenWidth - KillsImg->w) / 2,200,KillsImg,Screen);
				Dur = 20;
				Mag = 12;

				ClickDone = true;
				PieceOfPoo = true;
			}
		}

		if (PieceOfPoo == true)
		{
			ApplySurface((ScreenWidth - KillsImg->w) / 2,200,KillsImg,Screen); //Whats this?
			SpareStream.str("");
			SpareStream << Kills;
			Message = TTF_RenderText_Solid(EightBitLimitBig,SpareStream.str().c_str(),White);
			ApplySurface(((ScreenWidth - KillsImg->w) / 2) + (KillsImg->w - Message->w)/2, 200 + (KillsImg->h - Message->h)/2, Message, Screen);
			if (Counter < 180) Counter+=0.05;
			else Counter-=0.05;
			Message1 = TTF_RenderText_Solid(Takara,"R to restart",White);
			Message2 = rotozoomSurface(Message1,0,2 * sin(Counter),0);
			ApplySurface((ScreenWidth - Message2->w)/2,ScreenHeight - 80,Message2,Screen);
			//Kills = 500;
			std::ifstream ScoresInput;
			ScoresInput.open("TOD.DAT");
			ScoresInput >> Score1 >> Score2 >> Score3 >> HName1 >> HName2 >> HName3;
			ScoresInput.close();
			if(Kills > Score3 && ScoresDone == false)
			{
				std::vector <int> ScoreVector;
				std::string Name = "you";
				
				Name = GetStringInput();

				ScoreVector.push_back(Kills);
				ScoreVector.push_back(Score1);
				ScoreVector.push_back(Score2);
				ScoreVector.push_back(Score3);
				ScoreVector = BubbleSortVector(ScoreVector);
				ScoreVector.erase(ScoreVector.end() - 1, ScoreVector.end());
				
				std::string NameArray[4] = {Name,HName1,HName2,HName3};

				HName1 = NameArray[ICantCode.at(0)];
				HName2 = NameArray[ICantCode.at(1)];
				HName3 = NameArray[ICantCode.at(2)];

				Score1 = ScoreVector.at(0);
				Score2 = ScoreVector.at(1);
				Score3 = ScoreVector.at(2);
				
				std::ofstream ScoresOutput;
				ScoresOutput.open("TOD.DAT");
				ScoresOutput << Score1 << std::endl << Score2 << std::endl << Score3 << std::endl << HName1 << std::endl << HName2 << std::endl << HName3;
				ScoresOutput.close();
				ScoresDone = true;
			}
		}

		GetXYRatio(&xRatio,&yRatio,Mouse.MouseX,Mouse.MouseY,Character.WorldxPos - Viewport.CameraRect.x,Character.WorldyPos - Viewport.CameraRect.y);
		CalculateProjectileAngle(Character.WorldxPos - Viewport.CameraRect.x ,Character.WorldyPos - Viewport.CameraRect.y ,Mouse.MouseX,Mouse.MouseY);

		if(Debug == true)
		{
			
			if (Lives == 1) Lives = 4;
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
		}
		Viewport.MoveCameraTo(Character.WorldxPos - (ScreenWidth - Character.CurrentSprite->w)/2 , Character.WorldyPos - (ScreenHeight - Character.CurrentSprite->h)/2);
		
		if (StartProgress <= 90)
		{
			
			double Sign = sin(StartProgress * PI/180);
			double StartH = 0; 
			double StartO = 0;

			if (StartProgress > 10) 
			{
				double Sign2 = sin((StartProgress - 10) * PI/180);
				StartH = Sign2 * (ScreenWidth - 91) * 1.2;
			}

			if (StartProgress > 20)
			{
				double Sign3 = sin((StartProgress - 20) * PI/180);
				StartO = Sign3 * (ScreenWidth - 91) * 1.5;
			}

			ApplySurface(0, Sign * ScreenHeight,MenuBackground,Screen);
			ApplySurface(91 + Sign * (ScreenWidth - 91), 278, StartMouseOver,Screen);
			ApplySurface(91 + StartH, 318, HighscoresNormal,Screen);
			ApplySurface(91 + StartO, 358, OptionsNormal,Screen);
			StartProgress+=0.5;
		}
		
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
				int Spray = (rand () % 4 + 1) - 2;
				if (xRatio > 0)ProjectileVector.push_back(xRatio + Spray + Character.xVel);
				else ProjectileVector.push_back(xRatio - Spray + Character.xVel);
				ProjectileVector.push_back((yRatio * -1)+ Character.yVel);
				ProjectileVector.push_back(1);				
				MouseDown = true;
				Shot.start();
			}
			if(event.type == SDL_MOUSEBUTTONUP) MouseDown = false;
			if (event.type == SDL_KEYDOWN)
			{
				if (Ded == false)
				{
					if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) LDown = true;
					if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) RDown = true;
					if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) UDown = true;
					if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) DDown = true;
				}

				if (Ded == true && event.key.keysym.sym == SDLK_r)
				{
					State = MENU;
					Restart = true;
				}

				if(event.key.keysym.sym == SDLK_TAB) Debug = !Debug;

				if(event.key.keysym.sym == SDLK_n && Debug == true)
				{
					OpenDebugWindow("Open");
					Pause();
				}

				if(event.key.keysym.sym == SDLK_e && Debug == true)
				{
					__debugbreak();
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
				if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) LDown = false;
				if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) RDown = false;
				if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) UDown = false;
				if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) DDown = false;
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