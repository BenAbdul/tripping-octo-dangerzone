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
			State = HIGHSCORES;
			break; //no defaults
		case 3:
			State = OPTIONS;
		};
		SDL_Flip(Screen);
		CreateButton(91,278,1,StartNormal,StartMouseOver,3);
		CreateButton(91,318,2,HighscoresNormal,HighscoresMouseover,0);
		CreateButton(91,358,3,OptionsNormal,OptionsMouseover,0);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) Quit = true;
		}
	}
}