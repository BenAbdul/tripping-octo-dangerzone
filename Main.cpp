#include"Declarations.h"
#include"Menu.h"
#include"Game.h"

int main (int argc, char* argv [])
{
	if (Init() == false) return -1;
	LoadFiles();
	if (CheckFiles() == false) return -1;
	if (SetClips() == false) return -1;
	while (Quit == false)
	{
		switch(State)
		{
		case MENU:
			OpenDebugWindow("Entering Menu()");
			Menu();
			break;
		case GAME:
			OpenDebugWindow("Entering Game()");
			Game();
			break;
		}
	}
	return 0;
}
