#ifndef CURSOR_H
#define CURSOR_H
#include "SDL.h"
#include "Declarations.h"

class Cursor
{
public:
	int MouseX;
	int MouseY;
	int Frame, FrameTime;

	Cursor();
	void Render();
};

#endif