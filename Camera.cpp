#include"Camera.h"
#include "SDL.h"
#include "Player.h"

Camera::Camera()
{
	CameraRect.x = 0;
	CameraRect.y = 0;
	CameraRect.w = 800;
	CameraRect.h = 500;
	xOffSet = 0;
	yOffSet = 0;

}

void Camera::MoveCameraTo(int x, int y)
{
	CameraRect.x = x + xOffSet;
	CameraRect.y = y + yOffSet;

	if (CameraRect.x < -400) CameraRect.x = -400;
	if (CameraRect.x > 1200) CameraRect.x = 1200;
	if (CameraRect.y < -400) CameraRect.y = -400;
	if (CameraRect.y > 1400) CameraRect.y = 1400;
}
