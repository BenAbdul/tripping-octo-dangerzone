#include"Declarations.h"
#include"LoadFiles.h"

bool LoadFiles()
{
	Background = LoadImage("Resources/Images/Background.png");
	if (Background == NULL) return false;
	Character = LoadImage("Resources/Images/Character.png");
	if (Character == NULL) return false;
}