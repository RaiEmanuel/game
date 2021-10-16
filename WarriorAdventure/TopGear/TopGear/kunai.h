
#ifndef _KUNAI_H_
#define _KUNAI_H_

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

class Kunai : public Object
{
private:
    Sprite* spriteKunai = nullptr; //cena de fundo que corre para trás
    float speedX = -100.0f;
    

public:
    bool isExit = false;//indica se está dentro da cena

    Kunai(float posX, float posY, float velX);                   // construtor
    ~Kunai();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         