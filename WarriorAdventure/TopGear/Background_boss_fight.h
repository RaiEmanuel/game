
#ifndef _BACKGROUND_BOSS_FIGHT_H_
#define _BACKGROUND_BOSS_FIGHT_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
//#include "TileSet.h"             // folha de sprites
//#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
#include "Font.h"                // desenho de texto 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

//enum Direction { STRAIGHT, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Background_boss_fight : public Object
{
private:
    Sprite* spriteBackground_boss_fight = nullptr; //cena de fundo que corre para trás
public:
    //float speedX = -300.0f;
    Background_boss_fight();                   // construtor
    ~Background_boss_fight();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         