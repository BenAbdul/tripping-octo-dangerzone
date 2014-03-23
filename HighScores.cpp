#include"HighScores.h"
#include"Declarations.h"
/*
	CreateButton(91,278,1,StartNormal,StartMouseOver,3);
	CreateButton(91,318,2,HighscoresNormal,HighscoresMouseover,3);
	CreateButton(91,358,3,OptionsNormal,OptionsMouseover,3)
	*/
void HighScores()
{
	Message1 = TTF_RenderText_Solid(Takara,"Hall of Fame",White);
	SpareStream.str("");
	SpareStream << HName1 << ": " << Score1;
	Message2 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);
	SpareStream.str("");
	SpareStream << HName2 << ": " << Score2;
	Message3 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);
	SpareStream.str("");
	SpareStream << HName3 << ": " << Score3;
	Message4 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);

	for (double i = 90; i >= 0; i -= 0.5)
	{
		int Progress = ScreenWidth * sin(i * 3.14159265359 / 180);
		ApplySurface(Progress - ScreenWidth, 0, MenuBackground, Screen);
		ApplySurface(Progress - ScreenWidth + 91,278,StartNormal,Screen);
		ApplySurface(Progress - ScreenWidth + 91,318,HighscoresMouseover,Screen);
		ApplySurface(Progress - ScreenWidth + 91,358,OptionsNormal,Screen);

		ApplySurface(Progress,0,HighscoresBackground,Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message1->w) / 2),50,Message1,Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message2->w) / 2), 200, Message2, Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message3->w) / 2), 250, Message3, Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message4->w) / 2), 300, Message4, Screen);
		SDL_Flip(Screen);
		SDL_Delay(5);
	}
	
	ApplySurface(0,0,HighscoresBackground,Screen);
	ApplySurface((ScreenWidth + 350 - Message1->w) / 2,50,Message1,Screen);
	ApplySurface((ScreenWidth + 350 - Message2->w) / 2, 200, Message2, Screen);
	ApplySurface((ScreenWidth + 350 - Message3->w) / 2, 250, Message3, Screen);
	ApplySurface((ScreenWidth + 350 - Message4->w) / 2, 300, Message4, Screen);
	SDL_Flip(Screen);
	while(State == HIGHSCORES)
	{
		SDL_Delay(200);
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) State = MENU;
			else if (event.type == SDL_QUIT) {Quit = true; State = MENU;}
		}
	}
	for (double i = 0; i <= 90; i += 0.5)
	{
		int Progress = ScreenWidth * sin(i * 3.14159265359 / 180);
		ApplySurface(Progress - ScreenWidth, 0, MenuBackground, Screen);
		ApplySurface(Progress - ScreenWidth + 91,278,StartNormal,Screen);
		ApplySurface(Progress - ScreenWidth + 91,318,HighscoresMouseover,Screen);
		ApplySurface(Progress - ScreenWidth + 91,358,OptionsNormal,Screen);

		ApplySurface(Progress,0,HighscoresBackground,Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message1->w) / 2),50,Message1,Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message2->w) / 2), 200, Message2, Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message3->w) / 2), 250, Message3, Screen);
		ApplySurface(Progress +((ScreenWidth + 350 - Message4->w) / 2), 300, Message4, Screen);
		SDL_Flip(Screen);
		SDL_Delay(5);
	}
}