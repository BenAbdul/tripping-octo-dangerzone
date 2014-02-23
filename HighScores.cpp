#include"HighScores.h"	

void HighScores()
{
	ApplySurface(0,0,HighscoresBackground,Screen);
	Message1 = TTF_RenderText_Solid(Takara,"Hall of Fame",White);
	ApplySurface((ScreenWidth - Message1->w) / 2,100,Message1,Screen);
	SpareStream.str("");
	SpareStream << HName1 << ": " << Score1;
	Message1 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);
	ApplySurface((ScreenWidth - Message1->w) / 2, 200, Message1, Screen);
	SpareStream.str("");
	SpareStream << HName2 << ": " << Score2;
	Message1 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);
	ApplySurface((ScreenWidth - Message1->w) / 2, 250, Message1, Screen);
	SpareStream.str("");
	SpareStream << HName3 << ": " << Score3;
	Message1 = TTF_RenderText_Solid(EightBitLimit,SpareStream.str().c_str(),White);
	ApplySurface((ScreenWidth - Message1->w) / 2, 300, Message1, Screen);
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
	State = MENU;
}