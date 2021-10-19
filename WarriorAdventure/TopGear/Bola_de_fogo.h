
#ifndef _BOLA_DE_FOGO_H_
#define _BOLA_DE_FOGO_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
//#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto

#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

//enum Direction { STRAIGHT, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Bola_de_fogo : public Object
{
private:
    TileSet* bola_de_fogoSet;           // folha de sprites do carro
    Animation* bola_de_fogoAni;         // anima��o do carro
    float speedX = -100.0f;


public:
    bool isExit = false;//indica se est� dentro da cena

    Bola_de_fogo(float posX, float posY, float velX);                   // construtor
    ~Bola_de_fogo();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         