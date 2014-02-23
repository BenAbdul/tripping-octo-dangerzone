#include"Options.h"

void Options()
{
	Message1 = TTF_RenderText_Solid(KarmaFuture,"OPTIONS GO HERE",White);
	ApplySurface(0,0,HighscoresBackground,Screen);
	ApplySurface(0,100,Message1,Screen);
	SDL_Flip(Screen);
	SDL_Delay(3500);
	State = MENU;
}