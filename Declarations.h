#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_rotozoom.h"

extern SDL_Event event;

extern const int ScreenWidth;
extern const int ScreenHeight;
extern const int ScreenBBP;

extern SDL_Colour White;

extern Uint8 *ArrowStates;

extern SDL_Rect CursorClips[16];

extern SDL_Surface *Background;
extern SDL_Surface *Character1;
extern SDL_Surface *MenuBackground;
extern SDL_Surface *Screen;
extern SDL_Surface *Window;
extern SDL_Surface *CursorSheet;
extern SDL_Surface *PausedScreen;

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

extern enum Gamestate {MENU,GAME};
extern Gamestate State;

extern char* Asshole;

SDL_Surface *LoadImage( std::string filename );
bool Init();
void LoadFiles();
bool SetClips();
bool CheckFiles();
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip = NULL );

#endif