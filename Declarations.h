#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_rotozoom.h"
#include "OpenDebugWindow.h"
#include "EnemyClass.h"
#include "ButtonClass.h"
#include <fstream>

extern SDL_Event event;

extern std::stringstream SpareStream;
extern std::string HName1,HName2,HName3;

extern std::vector <double> ProjectileVector;
extern std::vector <int> ICantCode;
extern std::vector <Enemy> EnemyVector;

extern const int ScreenWidth;
extern const int ScreenHeight;
extern const int ScreenBBP;
extern const int Arena;

extern SDL_Colour White;
extern SDL_Colour Other;

extern Uint8 *ArrowStates;

extern SDL_Rect CursorClips[17];
extern SDL_Rect ProjectileClips[2];
extern SDL_Rect EnemyDownClipRect[7];
SDL_Rect IndicatorClips[];
extern SDL_Rect BottomWall;

extern SDL_Surface *Background;
extern SDL_Surface *HighscoresBackground;
extern SDL_Surface *HighscoresNormal;
extern SDL_Surface *HighscoresMouseover;
extern SDL_Surface *MenuBackground;
extern SDL_Surface *Screen;
extern SDL_Surface *Window;
extern SDL_Surface *CursorSheet;
extern SDL_Surface *StartNormal;
extern SDL_Surface *StartMouseOver;
extern SDL_Surface *PausedScreen;
extern SDL_Surface *OptionsNormal;
extern SDL_Surface *OptionsMouseover;
extern SDL_Surface *EnemuIndicator;
extern SDL_Surface *YouDied;
extern SDL_Surface *YouAreShit;
extern SDL_Surface *D1;
extern SDL_Surface *U1;
extern SDL_Surface *LivesIcon;
extern SDL_Surface *Background2;
extern SDL_Surface *L1;
extern SDL_Surface *R1;
extern SDL_Surface *FrontDed;
extern SDL_Surface *Projectile;
extern SDL_Surface *HighscoresNormal;
extern SDL_Surface *HighscoresMouseover;
extern SDL_Surface *HUD;
extern SDL_Surface *Sniper;
extern SDL_Surface *BigGrid;
extern SDL_Surface *SmallGrid;
extern SDL_Surface *SniperFlipped;
extern SDL_Surface *Message1;
extern SDL_Surface *Message2;
extern SDL_Surface *Message3;
extern SDL_Surface *Message4;
extern SDL_Surface *EnemyDownClips;
extern SDL_Surface *EnemyUpClips;
extern SDL_Surface *KillsImg;

extern TTF_Font *KarmaFuture;
extern TTF_Font *Takara;
extern TTF_Font *TakaraBig;
extern TTF_Font *EightBitLimit;
extern TTF_Font *EightBitLimitBig;
extern TTF_Font *EightBitLimitSmall;

extern bool Quit;
extern bool ScreenShake;
extern bool WasItInit;
extern bool LDown;
extern bool RDown;
extern bool LazyFlag2;
extern bool UDown;
extern bool DDown;
extern bool MouseDown;
extern bool PlsPlaySound;
extern bool LazyDebug;
extern bool Ded;
extern bool Restart;
extern bool ShallIRenderHim;

extern int CameraX;
extern int CameraY;
extern int XChange;
extern int Score1;
extern int Score2;
extern int Score3;
extern int YChange;
extern int KillerID;
extern int Kills;
extern int PlayerX;
extern int PlayerY;
extern int Lives;
extern int Mag, Dur;
extern int PlayerXVel, PlayerYVel;

extern enum Gamestate {MENU,GAME,HIGHSCORES,OPTIONS};
extern Gamestate State;

SDL_Surface *LoadImage( std::string filename );
bool Init();
void LoadFiles();
bool SetClips();
bool CheckFiles();
void CheckShake();
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip = NULL );

#endif