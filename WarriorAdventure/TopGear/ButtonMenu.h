#ifndef _BUTTONMENU_H_
#define _BUTTONMENU_H_
// ---------------------------------------------------------------------------------
#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 
#include "Wind.h"                // desenho de texto 

#include <sstream>
using std::stringstream;
// ---------------------------------------------------------------------------------
class ButtonMenu : public Object
{
private:
    Sprite* spriteButton = nullptr;
public:
   
    ButtonMenu(string button, float posX, float posY);                   // construtor
    ~ButtonMenu();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colis�es do objeto
};
#endif