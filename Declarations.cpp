#include"Declarations.h"
#include "OpenDebugWindow.h"

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	if(TTF_Init() == -1) return false;
	WasItInit = TTF_WasInit();
	Screen = SDL_SetVideoMode(ScreenWidth,ScreenHeight,ScreenBBP,SDL_SWSURFACE);
	if (Screen == NULL) return false;
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) return false;
    SDL_WM_SetCaption("Tripping Octo Dangerzone", NULL);
    SDL_EnableUNICODE(SDL_ENABLE);
    return true;
}

SDL_Surface *LoadImage( std::string filename )
{
    SDL_Surface* LoadedImage = NULL;
    SDL_Surface* OptimizedImage = NULL;
        LoadedImage = IMG_Load( filename.c_str() );
    if( LoadedImage != NULL )
    {
        OptimizedImage = SDL_DisplayFormatAlpha( LoadedImage );
        SDL_FreeSurface( LoadedImage );
    }
    return OptimizedImage;
}
 
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip)
{
    SDL_Rect offset;
	offset.x = x;
    offset.y = y;
    SDL_BlitSurface( Source, Clip, Destination, &offset );
}

SDL_Event event;

bool WasItInit = false;
bool LDown = false;
bool RDown = false;
bool UDown = false;
bool DDown = false;

std::stringstream SpareStream;

const int ScreenWidth = 800;
const int ScreenHeight = 500;
const int ScreenBBP = 32;

SDL_Colour White = {225,225,225};

Uint8 *ArrowStates = SDL_GetKeyState(NULL);

SDL_Rect CursorClips[16];

SDL_Surface *Screen = NULL;
SDL_Surface *Background = NULL;
SDL_Surface *Character1 = NULL;
SDL_Surface *MenuBackground = NULL;
SDL_Surface *CursorSheet = NULL;
TTF_Font *EightBitLimit = NULL;
TTF_Font *KarmaFuture = NULL;
TTF_Font *EightBitLimitSmall = NULL;
SDL_Surface *Message1 = NULL;
SDL_Surface *Message2 = NULL;
SDL_Surface *PausedScreen = NULL;
SDL_Surface *Window = NULL;

void LoadFiles()
{
	Screen = SDL_SetVideoMode(ScreenWidth,ScreenHeight,ScreenBBP,SDL_SWSURFACE);
	Background = LoadImage("Resources/Images/Background.png");
	Character1 = LoadImage("Resources/Images/Character.png");
	MenuBackground = LoadImage("Resources/Images/MenuBackground.png");
	CursorSheet = LoadImage("Resources/Images/Cursor.png");
	PausedScreen = LoadImage("Resources/Images/PauseScreen.png");
	EightBitLimit = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",26);
	KarmaFuture = TTF_OpenFont("Resources/Fonts/KarmaFuture.ttf",34);
	EightBitLimitSmall = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",16);
}

bool SetClips()
{
	SpareStream.str("");
	SpareStream << "CursorSheets width is " << CursorSheet->w;
	OpenDebugWindow(SpareStream.str());
	for(int x = 0; x < 16; x++)
	{
		CursorClips[x].x = (x * 38);
		CursorClips[x].y = 0;
		CursorClips[x].w = 38;
		CursorClips[x].h = 38;
		if (x == 15) CursorClips[x].w = 34;
		SpareStream.str("");
		SpareStream << "Cursor frame " << x << " begins at x = " << CursorClips[x].x << " and ends at " << CursorClips[x].x + CursorClips[x].w;
		OpenDebugWindow(SpareStream.str());
	}
	if (CursorClips[2].w == 0) return false;
	return true;
}

bool CheckFiles()
{
	WasItInit = TTF_WasInit();
	if (Background == NULL) return false;
	else if (Character1 == NULL) return false;
	else if (MenuBackground == NULL) return false;
	else if (EightBitLimit == NULL) return false;
	else if (CursorSheet == NULL) return false;
	else if (KarmaFuture == NULL) return false;
	else if (EightBitLimitSmall == NULL) return false;
	else if (PausedScreen == NULL) return false;
	OpenDebugWindow("All files loaded successfully");
	return true;
}

bool Quit = false;

Gamestate State = MENU;
