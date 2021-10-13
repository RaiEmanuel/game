#ifndef _PLAYER_H_
#define _PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

enum StatePlayer { IDLE, RUN, ATTACK, JUMP, FALL };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet * playerSet;           // folha de sprites do carro
    Animation * playerAni;         // anima��o do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = 300.0f;              // velocidade do carro
    float speedY = 0.0f;              // velocidade do carro
    stringstream text;          // exibi��o de texto
    Timer timerJump;            //controla tempo do pulo
    bool releaseTimerJump = false; //controla libera��o do timer do pulo, true significa que pode disparar pulo
    float initYJump = 0.0f;
    bool onBlock = false; //verifica se est� num bloco na itera��o
    StatePlayer statePlayer = FALL;
    const float gravity = 50.0f;
public:
    Player();                   // construtor
    ~Player();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object * obj);                // colis�es do objeto
}; 

// ---------------------------------------------------------------------------------

#endif