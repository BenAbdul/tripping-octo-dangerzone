#include"Declarations.h"
#include<time.h>

void PlayRandomMusic()
{
	if (PlsPlaySound == true)
	{
		srand((time(NULL) * time(NULL)) / 100);
		int ChosenSong = rand () %  8 + 1;
		OpenDebugWindow("Loading and playing...");
		SpareStream.str("");
		SpareStream << "Resources/Sounds/Music/" << ChosenSong << ".ogg";
		OpenDebugWindow(SpareStream.str());
		Mix_Music *Music = Mix_LoadMUS(SpareStream.str().c_str());
		Mix_PlayMusic(Music,-1);
	}
}