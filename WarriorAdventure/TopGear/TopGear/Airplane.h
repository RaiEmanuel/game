#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 
#include "Tiro_aviao.h" 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------



class Airplane : public Object
{
   
private:
    TileSet* airplaneSet;           // folha de sprites do carro
    Animation* airplaneAni;         // anima��o do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = -200.0f;              // velocidade do avi�o
    float speedY = 0.0f;              // velocidade do avi�o
    stringstream text;          // exibi��o de texto
    //Timer timerJump;            //controla tempo do pulo
   // bool releaseTimerJump = false; //controla libera��o do timer do pulo, true significa que pode disparar pulo
    //float initYJump = 0.0f;
    

public:
   

    Airplane();                   // construtor
    ~Airplane();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colis�es do objeto
};

// ---------------------------------------------------------------------------------

#endif