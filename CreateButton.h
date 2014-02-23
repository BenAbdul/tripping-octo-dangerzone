#ifndef CREATEBUTTON_H
#define CREATEBUTTON_H

#include"ButtonClass.h"
#include"Declarations.h"

extern std::vector <Button> ButtonVector;

extern void CreateButton(int Wx, int Wy, int WID,SDL_Surface *WUnPressed, SDL_Surface *WPressed, int LOffset);
extern int DoButtons();
extern void ClearButtons();
#endif