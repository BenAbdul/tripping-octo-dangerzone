#include"Declarations.h"
#include"Menu.h"

void Menu()
{
	while (Quit == false && State == MENU)
	{
		ApplySurface(0,0,MenuBackground,Screen);
		Message1 = TTF_RenderText_Solid(KarmaFuture,"Tripping Octo Dangerzone",White);
		Message2 = TTF_RenderText_Solid(EightBitLimit,"Press Enter to begin", White);
		ApplySurface ((800 - Message1->w)/2, 100, Message1, Screen);
		ApplySurface ((800 - Message2->w)/2, 200, Message2, Screen);
		SDL_Flip(Screen);
		while (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) Quit = true;
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) State = GAME;
		}
	}
}