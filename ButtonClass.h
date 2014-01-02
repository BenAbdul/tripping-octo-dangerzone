#ifndef BUTTONCLASS_H
#define BUTTONCLASS_H
#include"Declarations.h"
#include"OpenDebugWindow.h"

class Button
{
public:
	SDL_Rect ButtonRect;
	SDL_Surface *Normal;
	SDL_Surface *NotNormal;

	int ID;
	 
	Button();
	bool IsMouseOver(int Mx, int My);
};

#endif