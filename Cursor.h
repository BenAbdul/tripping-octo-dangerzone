#ifndef CURSOR_H
#define CURSOR_H

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