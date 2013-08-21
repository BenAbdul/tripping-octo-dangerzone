#include"Declarations.h"

void Pause()
{
	bool Resumed = false;
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_ShowCursor(SDL_ENABLE);
	ApplySurface(0,0,PausedScreen,Screen);
	SDL_Flip(Screen);
	while (Quit == false && Resumed == false)
	{
		SDL_Delay(500);
		while(SDL_PollEvent(&event))
		{
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) Resumed = true;
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) Quit = true;
		}
	}
	SDL_WM_GrabInput( SDL_GRAB_ON );
	SDL_ShowCursor(SDL_DISABLE);
}