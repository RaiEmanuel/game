
#ifndef _PHONE_H_
#define _PHONE_H_

// ---------------------------------------------------------------------------------
#include "Object.h"              // objetos do jogo
#include "Types.h"               // tipos específicos do motor
#include "Sprite.h"               // tipos específicos do motor
#include <sstream>
using std::stringstream;

class Phone : public Object
{
private:
    Sprite* spritePhone = nullptr; //cena de fundo que corre para trás

public:
    Phone(float posX, float posY);                   // construtor
    ~Phone();                  // destrutor

    void Draw();                // desenha objeto
    void Update();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         