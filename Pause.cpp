#include"Declarations.h"

void Pause()
{
	bool Resumed = false;
	ApplySurface(0,0,PausedScreen,Screen);
	SDL_Flip(Screen);
	while (Quit == false && Resumed == false && State == GAME)
	{
		SDL_Delay(500);
		while(SDL_PollEvent(&event))
		{
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {Resumed = true; SDL_WM_GrabInput( SDL_GRAB_ON ); SDL_ShowCursor(SDL_DISABLE);}
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {State = MENU; Restart = true;}
		}
	}
}