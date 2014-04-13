#include"Declarations.h"
#include"CreateButton.h"
#include"PlayRandomMusic.h"
#include"Menu.h"

void Menu()
{
	PlayRandomMusic();
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_ShowCursor(SDL_ENABLE);
	CreateButton(91,278,1,StartNormal,StartMouseOver,3);
	CreateButton(91,318,2,HighscoresNormal,HighscoresMouseover,3);
	CreateButton(91,358,3,OptionsNormal,OptionsMouseover,3);
	while (Quit == false && State == MENU)
	{
		SDL_Delay(10);
		ApplySurface(0,0,MenuBackground,Screen);
		int Clicked = DoButtons();
		switch(Clicked)
		{
		case 1:
			ClearButtons();
			State = GAME;
			break;
		case 2:
			ClearButtons();
			State = HIGHSCORES;
			break; //no defaults
		case 3:
			ClearButtons();
			State = OPTIONS;
		};
		SDL_Flip(Screen);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) Quit = true;
		}
	}
}