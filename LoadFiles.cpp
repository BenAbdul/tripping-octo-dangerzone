#include"Declarations.h"
#include"LoadFiles.h"

bool LoadFiles()
{
	Background = LoadImage("Resources/Images/Background.png");
	if (Background == NULL) return false;
	Character1 = LoadImage("Resources/Images/Character.png");
	if (Character1 == NULL) return false;
	MenuBackground = LoadImage("Resources/Images/MenuBackground.png");
	if (MenuBackground == NULL) return false;

	EightBitLimit = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",16);
	if (EightBitLimit == NULL) return false;
	KarmaFuture = TTF_OpenFont("Resources/Fonts/KarmaFuture.ttf",16);
	if (KarmaFuture == NULL) return false;
	EightBitLimitSmall = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",9);
	if (EightBitLimitSmall == NULL) return false;

	return true;
}