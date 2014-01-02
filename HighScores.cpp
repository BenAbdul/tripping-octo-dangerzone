#include"HighScores.h"	

void HighScores()
{
	ApplySurface(0,0,HighscoresBackground,Screen);
	SDL_Flip(Screen);
	SDL_Delay(3500);
	State = MENU;
}