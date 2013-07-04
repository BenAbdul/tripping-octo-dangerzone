#include"Declarations.h"

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
 
void ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip = NULL )
{
    SDL_Rect offset;
    SDL_BlitSurface( Source, Clip, Destination, &offset );
}