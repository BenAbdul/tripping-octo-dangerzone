#include"Camera.h"
#include"Declarations.h"
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
	if (CameraRect.x > Arena - 800) CameraRect.x = Arena - 800;
	if (CameraRect.y < -400) CameraRect.y = -400;
	if (CameraRect.y > Arena - 500) CameraRect.y = Arena - 800;
}
