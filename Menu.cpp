#include"Declarations.h"
#include"CreateButton.h"
#include"Menu.h"

void Menu()
{
	while (Quit == false && State == MENU)
	{
		SDL_Delay(10);
		ApplySurface(0,0,MenuBackground,Screen);
		int Clicked = DoButtons();
		switch(Clicked)
		{
		case 1:
			State = GAME;
			break;
		case 2:
			//__debugbreak();
			State = HIGHSCORES;
			break; //no defaults
		};
		SDL_Flip(Screen);
		CreateButton(91,278,1,StartNormal,StartMouseOver);
		CreateButton(91,318,2,HighscoresNormal,HighscoresMouseover);
	}
}