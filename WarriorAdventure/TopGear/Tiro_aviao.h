
#ifndef _TIRO_AVIAO_H_
#define _TIRO_AVIAO_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
//#include "TileSet.h"             // folha de sprites
//#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
#include "Font.h"                // desenho de texto 
#include "block.h"        
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

//enum Direction { STRAIGHT, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Tiro_aviao : public Object
{
private:
    Sprite* spriteTiro_aviao = nullptr; //cena de fundo que corre para trás
    float speedY = 100.0f;
    float speedX = Block::speedX - 300.0f;
    float gravity = 5.0f;


public:
    bool isExit = false;//indica se está dentro da cena

    Tiro_aviao(float posX, float posY);                   // construtor
    ~Tiro_aviao();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         