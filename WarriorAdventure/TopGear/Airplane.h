#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
#include "Font.h"                // desenho de texto 
#include "Tiro_aviao.h" 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------



class Airplane : public Object
{
   
private:
    TileSet* airplaneSet;           // folha de sprites do carro
    Animation* airplaneAni;         // animação do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = -200.0f;              // velocidade do avião
    float speedY = 0.0f;              // velocidade do avião
    stringstream text;          // exibição de texto
    //Timer timerJump;            //controla tempo do pulo
   // bool releaseTimerJump = false; //controla liberação do timer do pulo, true significa que pode disparar pulo
    //float initYJump = 0.0f;
    

public:
   

    Airplane();                   // construtor
    ~Airplane();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colisões do objeto
};

// ---------------------------------------------------------------------------------

#endif