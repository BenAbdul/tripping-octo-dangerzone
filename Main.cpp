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
			State = GAME;
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
	return 0;
}
