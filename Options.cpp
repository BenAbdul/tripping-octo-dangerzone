#include"Options.h"
#include<fstream>
#include"ButtonClass.h"
#include"CreateButton.h"

void Options()
{
	ApplySurface(0,0,HighscoresBackground,Screen);
	
	SDL_Surface *On = TTF_RenderText_Solid(KarmaFuture,"On",White);
	SDL_Surface *Off = TTF_RenderText_Solid(KarmaFuture,"Off",White);

	ClearButtons();

	Message1 = TTF_RenderText_Solid(KarmaFuture,"Play Sound",White);
	Message2 = TTF_RenderText_Solid(KarmaFuture,"Play Sound",Other);
	CreateButton(200,50,1,Message1,Message2,0);

	Message1 = TTF_RenderText_Solid(KarmaFuture,"Screen Shake",White);
	Message2 = TTF_RenderText_Solid(KarmaFuture,"Screen Shake",Other);
	CreateButton(200,150,2,Message1,Message2,0);

	Message1 = TTF_RenderText_Solid(KarmaFuture,"Reset High Scores",White);
	Message2 = TTF_RenderText_Solid(KarmaFuture,"Reset High Scores",Other);
	CreateButton(200,250,3,Message1,Message2,0);

	Message1 = TTF_RenderText_Solid(KarmaFuture,"Back",White);
	Message2 = TTF_RenderText_Solid(KarmaFuture,"Back",Other);
	CreateButton(200,350,4,Message1,Message2,0);

	bool Done = false;

	while (Done == false)
	{
		ApplySurface(0,0,Background,Screen);


		while(SDL_PollEvent(&event)) {if (event.type == SDL_QUIT) {Quit = true; State = MENU; Done = true;}
		else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN)) Done = true;}
		
		if(PlsPlaySound == true) ApplySurface(450,50,On,Screen);
		else ApplySurface(450,50,Off,Screen);
		
		if(ScreenShake == true) ApplySurface(450,150,On,Screen);
		else ApplySurface(450,150,Off,Screen);

		std::ofstream FileOutput;
		int Clicked = DoButtons();
		switch(Clicked)
		{
		case 1:
			PlsPlaySound = !PlsPlaySound;
			break;
		case 2:
			ScreenShake = !ScreenShake;
			break;
		case 3:
			FileOutput.open("TOD.DAT");
			FileOutput << 150 << std::endl << 100  << std::endl << 75 << std::endl << "Default1" << std::endl << "Default2" << std::endl << "Default3" << std::endl;
			FileOutput.close();
			break;
		case 4:
			Done = true;
			break;
		}
		SDL_Flip(Screen);
		SDL_Delay(100);
	}
	ClearButtons();
	State = MENU;
}
