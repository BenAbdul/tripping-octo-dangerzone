#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_rotozoom.h"

const int ScreenWidth = 800;
const int ScreenHeight = 500;
const int ScreenBBP = 32;

Uint8 *ArrowStates = SDL_GetKeyState(NULL);

SDL_Surface *Background = NULL;
SDL_Surface *Character = NULL;
SDL_Surface *Screen = NULL;

SDL_Surface *LoadImage( std::string filename );
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip = NULL );
