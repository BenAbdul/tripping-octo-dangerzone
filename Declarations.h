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

extern SDL_Event event;

extern std::stringstream SpareStream;

extern std::vector <double> ProjectileVector;

extern const int ScreenWidth;
extern const int ScreenHeight;
extern const int ScreenBBP;
extern const int Arena;

extern SDL_Colour White;

extern Uint8 *ArrowStates;

extern SDL_Rect CursorClips[17];
extern SDL_Rect ProjectileClips[2];
extern SDL_Rect BottomWall;

extern SDL_Surface *Background;
extern SDL_Surface *MenuBackground;
extern SDL_Surface *Screen;
extern SDL_Surface *Window;
extern SDL_Surface *CursorSheet;
extern SDL_Surface *PausedScreen;
extern SDL_Surface *RShadow;
extern SDL_Surface *LShadow;
extern SDL_Surface *Shadow;
extern SDL_Surface *D1;
extern SDL_Surface *U1;
extern SDL_Surface *L1;
extern SDL_Surface *R1;
extern SDL_Surface *Projectile;
extern SDL_Surface *HUD;
extern SDL_Surface *Sniper;
extern SDL_Surface *Message1;
extern SDL_Surface *Message2;

extern TTF_Font *KarmaFuture;
extern TTF_Font *EightBitLimit;
extern TTF_Font *EightBitLimitSmall;

extern bool Quit;
extern bool WasItInit;
extern bool LDown;
extern bool RDown;
extern bool UDown;
extern bool DDown;
extern bool PlaySound;

extern int CameraX;
extern int CameraY;
extern int XChange;
extern int YChange;
extern int EnemyID;

extern enum Gamestate {MENU,GAME};
extern Gamestate State;

SDL_Surface *LoadImage( std::string filename );
bool Init();
void LoadFiles();
bool SetClips();
bool CheckFiles();
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip = NULL );

#endif