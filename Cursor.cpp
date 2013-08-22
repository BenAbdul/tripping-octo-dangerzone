#include "Cursor.h"
#include "Declarations.h"

Cursor::Cursor()
{
	int MouseX = 400;
	int MouseY = 250;
	int Frame = 0;
	int FrameTime = 0;
}

void Cursor::Render()
{
	if (FrameTime < 0) FrameTime = 0;
	if (Frame < 0) Frame = 0;
	FrameTime++;
	if (FrameTime == 4)
	{
		Frame++;
		FrameTime = 0;
	}
	if (Frame == 15) Frame = 0;
	ApplySurface(MouseX - 19, MouseY - 19, CursorSheet ,Screen , &CursorClips[Frame]);
}