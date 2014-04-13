#include"Declarations.h"
#include"Menu.h"
#include"Game.h"
#include"HighScores.h"
#include"Options.h"
#include<time.h>

int main (int argc, char* argv [])
{
	if (Init() == false) return -1;
	srand(time(NULL));
	OpenDebugWindow("Loading files");
	LoadFiles();
	if (CheckFiles() == false) 
	{
		system("PAUSE");
		return -1;
	}
	if (SetClips() == false) return -1;

	while (Quit == false)
	{
		if (Restart == true)
		{
			Ded = false;
			Lives = 4;
			EnemyVector.erase(EnemyVector.begin(),EnemyVector.end());
			ProjectileVector.erase(ProjectileVector.begin(),ProjectileVector.end());
			int CameraX = 0;
			CameraY = 0;
			XChange = 0;
			YChange = 0;
			Kills = 0;
			KillerID = 0;
			PlayerX, PlayerY = 0;
			PlayerXVel, PlayerYVel = 0;
			Lives = 4;
			Restart = false;
		}
		switch(State)
		{
		case MENU:
			Menu();
			break;
		case GAME:
			Game();
			break;
		case HIGHSCORES:
			HighScores();
			break;
		case OPTIONS:
			Options();
			break;
		}
	}

	SDL_FreeSurface(Screen);
	SDL_FreeSurface(Background);
	SDL_FreeSurface(HighscoresBackground);
	SDL_FreeSurface(StartNormal);
	SDL_FreeSurface(StartMouseOver);
	SDL_FreeSurface(MenuBackground);
	SDL_FreeSurface(CursorSheet);
	SDL_FreeSurface(YouDied);
	SDL_FreeSurface(YouAreShit);
	SDL_FreeSurface(Message1);
	SDL_FreeSurface(LivesIcon);
	SDL_FreeSurface(Message2);
	SDL_FreeSurface(Message3);
	SDL_FreeSurface(Message4);
	SDL_FreeSurface(PausedScreen);
	SDL_FreeSurface(Background2);
	SDL_FreeSurface(HighscoresNormal);
	SDL_FreeSurface(HighscoresMouseover);
	SDL_FreeSurface(OptionsNormal);
	SDL_FreeSurface(OptionsMouseover);
	SDL_FreeSurface(Window);
	SDL_FreeSurface(U1);
	SDL_FreeSurface(SmallGrid);
	SDL_FreeSurface(BigGrid);
	SDL_FreeSurface(FrontDed);
	SDL_FreeSurface(D1);
	SDL_FreeSurface(L1);
	SDL_FreeSurface(R1);
	SDL_FreeSurface(Projectile);
	SDL_FreeSurface(HUD);
	SDL_FreeSurface(KillsImg);
	SDL_FreeSurface(Sniper);
	SDL_FreeSurface(SniperFlipped);
	SDL_FreeSurface(EnemuIndicator);
	SDL_FreeSurface(EnemyDownClips);
	SDL_FreeSurface(EnemyUpClips);

	return 0;
}
