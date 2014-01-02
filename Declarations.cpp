#include"Declarations.h"
#include "OpenDebugWindow.h"
#include "DoEnemies.h"

SDL_Surface *LoadImage( std::string filename )
{
    OpenDebugWindow(filename);
	SDL_Surface* LoadedImage = NULL;
    SDL_Surface* OptimizedImage = NULL;
        LoadedImage = IMG_Load( filename.c_str() );
    if( LoadedImage != NULL )
    {
        OptimizedImage = SDL_DisplayFormatAlpha( LoadedImage );
        SDL_FreeSurface( LoadedImage );
    }
	else 
	{
		OpenDebugWindow("Failed to load last file");
		OpenDebugWindow("Open");
	}
    return OptimizedImage;
}

int CameraX = 0;
int CameraY = 0;
int XChange = 0;
int YChange = 0;
int Kills = 0;
int KillerID = 0;
int PlayerX, PlayerY = 0;
int PlayerXVel, PlayerYVel = 0;
int Lives = 4;

SDL_Event event;

bool WasItInit = false;
bool Quit = false;
bool Restart = false;
bool LDown = false;
bool RDown = false;
bool UDown = false;
bool DDown = false;
bool Ded = false;
bool LazyFlag2 = false;
bool MouseDown = false;
bool PlsPlaySound = true;
bool LazyDebug = false;
bool ShallIRenderHim = true;

std::stringstream SpareStream;

std::vector <double> ProjectileVector;
std::vector <Enemy> EnemyVector;

const int ScreenWidth = 800;
const int ScreenHeight = 500;
const int ScreenBBP = 32;
const int Arena = 6000;

SDL_Colour White = {225,225,225};

Uint8 *ArrowStates = SDL_GetKeyState(NULL);

SDL_Rect CursorClips[17];
SDL_Rect ProjectileClips[2];
SDL_Rect EnemyDownClipRect[7];
SDL_Rect IndicatorClips[8];

SDL_Surface *Screen = NULL;
SDL_Surface *Background = NULL;
SDL_Surface *HighscoresBackground = NULL;
SDL_Surface *StartNormal = NULL;
SDL_Surface *StartMouseOver = NULL;
SDL_Surface *MenuBackground = NULL;
SDL_Surface *CursorSheet = NULL;
SDL_Surface *YouDied = NULL;
SDL_Surface *YouAreShit = NULL; 
TTF_Font *EightBitLimit = NULL;
TTF_Font *EightBitLimitBig = NULL;
TTF_Font *KarmaFuture = NULL;
TTF_Font *EightBitLimitSmall = NULL;
SDL_Surface *Message1 = NULL;
SDL_Surface *LivesIcon = NULL;
SDL_Surface *Message2 = NULL;
SDL_Surface *PausedScreen = NULL;
SDL_Surface *Background2 = NULL;
SDL_Surface *HighscoresNormal = NULL;
SDL_Surface *HighscoresMouseover = NULL;
SDL_Surface *Window = NULL;
SDL_Surface *U1 = NULL;
SDL_Surface *SmallGrid = NULL;
SDL_Surface *BigGrid = NULL;
SDL_Surface *FrontDed = NULL;
SDL_Surface *D1 = NULL;
SDL_Surface *L1 = NULL;
SDL_Surface *R1 = NULL;
SDL_Surface *Projectile = NULL;
SDL_Surface *HUD = NULL;
SDL_Surface *KillsImg = NULL;
SDL_Surface *Sniper = NULL;
SDL_Surface *SniperFlipped = NULL;
SDL_Surface *EnemuIndicator = NULL;
SDL_Surface *EnemyDownClips = NULL;
SDL_Surface *EnemyUpClips = NULL;

void LoadFiles()
{
	Screen = SDL_SetVideoMode(ScreenWidth,ScreenHeight,ScreenBBP,SDL_SWSURFACE);
	Background = LoadImage("Resources/Images/Background.png");
	EnemuIndicator = LoadImage("Resources/Images/Indicators.png");
	CursorSheet = LoadImage("Resources/Images/Cursor.png");
	PausedScreen = LoadImage("Resources/Images/PauseScreen.png");
	BigGrid = LoadImage("Resources/Images/25grid.png");
	SmallGrid = LoadImage("Resources/Images/10grid.png");
	MenuBackground = LoadImage("Resources/Images/TempMenu.png");
	EightBitLimit = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",26);
	EightBitLimitBig = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",70);
	KarmaFuture = TTF_OpenFont("Resources/Fonts/KarmaFuture.ttf",34);
	EightBitLimitSmall = TTF_OpenFont("Resources/Fonts/EightBitLimit.ttf",16);
	U1 = LoadImage("Resources/Images/Character/U1.png");
	D1 = LoadImage("Resources/Images/Character/D1.png");
	L1 = LoadImage("Resources/Images/Character/L1.png");
	R1 = LoadImage("Resources/Images/Character/R1.png");
	StartNormal = LoadImage("Resources/Images/Start.png");
	StartMouseOver = LoadImage("Resources/Images/StartMouseOver.png");
	LivesIcon = LoadImage("Resources/Images/Life.png");
	HighscoresNormal = LoadImage("Resources/Images/HighscoresNormal.png");
	HighscoresMouseover = LoadImage("Resources/Images/HighscoresMouseover.png");
	EnemyDownClips = LoadImage("Resources/Images/EnemyDownwards.png");
	EnemyUpClips = LoadImage("Resources/Images/EnemyUpwards.png");
	HighscoresBackground = LoadImage("Resources/Images/HighscoresBackground.png");
	YouDied = LoadImage("Resources/Images/YouDied.png");
	Background2 = LoadImage("Resources/Images/Background2.png");
	YouAreShit = LoadImage("Resources/Images/YouAreShit.png");
	Projectile = LoadImage("Resources/Images/TempProjectile.png");
	HUD = LoadImage("Resources/Images/UI.png");
	FrontDed = LoadImage("Resources/Images/TempDed.png");
	Sniper = LoadImage("Resources/Images/LeSniper.png");
	SniperFlipped = LoadImage("Resources/Images/LeSniperFlipped.png");
	KillsImg = LoadImage("Resources/Images/Kills.png");
}

int Dur, Mag;

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
	}

	for(int x = 0; x < 8; x++)
	{
		EnemyDownClipRect[x].x = (x * 49);
		EnemyDownClipRect[x].y = 0;
		EnemyDownClipRect[x].w = 49;
		EnemyDownClipRect[x].h = 36;
	}

	for(int x = 0; x < 9; x++)
	{
		IndicatorClips[x].x = (x * 50);
		IndicatorClips[x].y = 0;
		IndicatorClips[x].w = 50;
		IndicatorClips[x].h = 50;
	}
	
	ProjectileClips[0].h = 11;
	ProjectileClips[0].w = 11;
	ProjectileClips[0].x = 0;
	ProjectileClips[0].y = 0;

	ProjectileClips[1].h = 11;
	ProjectileClips[1].w = 11;
	ProjectileClips[1].x = 12;
	ProjectileClips[1].y = 0;

	if (CursorClips[2].w == 0) return false;
	return true;
}

void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip)
{
    SDL_Rect offset;
	offset.x = x + XChange;
    offset.y = y + YChange;
    SDL_BlitSurface( Source, Clip, Destination, &offset );
}

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

	XChange = 0;
	YChange = 0;
}

bool CheckFiles()
{
	WasItInit = TTF_WasInit();
	if (Background == NULL) {OpenDebugWindow("Background failed to load!"); return false;}
	else if (MenuBackground == NULL) {OpenDebugWindow("MenuBackground failed to load!");return false;}
	else if (EightBitLimit == NULL) {OpenDebugWindow("Bens font failed to load!");return false;}
	else if (CursorSheet == NULL) {OpenDebugWindow("CursorSheet failed to load!");return false;}
	else if (KarmaFuture == NULL) {OpenDebugWindow("KarmaFuture failed to load!");return false;}
	else if (EightBitLimitSmall == NULL) {OpenDebugWindow("Bens font small failed to load!");return false;}
	else if (PausedScreen == NULL) {OpenDebugWindow("Pause screen failed to load!");return false;}
	else if (FrontDed == NULL) {OpenDebugWindow("Frontded failed to load!");return false;}
	else if (HighscoresNormal == NULL) {OpenDebugWindow("High Scores Normal failed to load!");return false;}
	else if (HighscoresMouseover == NULL) {OpenDebugWindow("High Scores Mouseover failed to load!");return false;}
	else if (U1 == NULL) {OpenDebugWindow("U1 failed to load!");return false;}
	else if (R1 == NULL) {OpenDebugWindow("R1 failed to load!");return false;}
	else if (D1 == NULL) {OpenDebugWindow("D1 failed to load!");return false;}
	else if (L1 == NULL) {OpenDebugWindow("L1 failed to load!");return false;}
	else if (StartNormal == NULL) {OpenDebugWindow("StartNormal failed to load!");return false;}
	else if (StartMouseOver == NULL) {OpenDebugWindow("StartMouseOver failed to load!");return false;}
	else if (KillsImg == NULL) {OpenDebugWindow("KillsImg failed to load!");return false;}
	else if (YouDied == NULL) {OpenDebugWindow("YouDied failed to load!");return false;}
	else if (LivesIcon == NULL) {OpenDebugWindow("LivesIcon failed to load!");return false;}
	else if (YouAreShit == NULL) {OpenDebugWindow("You'reShit failed to load!");return false;}
	else if (Projectile == NULL) {OpenDebugWindow("Projectile failed to load!");return false;}
	else if (BigGrid == NULL) {OpenDebugWindow("BigGrid failed to load!");return false;}
	else if (SmallGrid == NULL) {OpenDebugWindow("SmallGrid failed to load!");return false;}
	else if (SniperFlipped == NULL) {OpenDebugWindow("Flipped sniper failed to load!");return false;}
	else if (Sniper == NULL) {OpenDebugWindow("Sniper failed to load!");return false;}
	else if (EnemyDownClips == NULL) {OpenDebugWindow("EnemyDownClips failed to load!");return false;}
	else if (EnemyUpClips == NULL) {OpenDebugWindow("EnemyUpClips failed to load!");return false;}
	else if (EnemuIndicator == NULL) {OpenDebugWindow("Enemy indicator failed to load!");return false;}
	else if (HighscoresBackground == NULL) {OpenDebugWindow("Highscores Background indicator failed to load!");return false;}
	else if (Background2 == NULL) {OpenDebugWindow("Background2 failed to load!");return false;}
	OpenDebugWindow("All files loaded successfully");
	return true;
	
}

Gamestate State = MENU;
