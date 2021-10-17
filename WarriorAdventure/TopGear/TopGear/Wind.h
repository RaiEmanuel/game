
#ifndef _WIND_H_
#define _WIND_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
//#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
#include "Font.h"                // desenho de texto 
//#include "block.h"        
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------
//enum Direction { STRAIGHT, LEFT, RIGHT };
// ---------------------------------------------------------------------------------
class Wind : public Object
{
private:
    TileSet* windSet;           // folha de sprites do carro
    Animation* windAni;         // animação do carro
    float speedX = 200.0f;
public:
    //bool isExit = false;//indica se está dentro da cena
    Wind(float posX, float posY);                   // construtor
    ~Wind();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         