#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"

class Camera
{
public:
	SDL_Rect CameraRect;
	int xOffSet, yOffSet;
	Camera();
	void MoveCameraTo(int x, int y);
};

#endif