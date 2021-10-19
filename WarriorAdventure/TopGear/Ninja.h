#ifndef _NINJA_H_
#define _NINJA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 

#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

struct ThrowKunai {
    float posX = 500.0f;
    float posY = 500.0f;
    float velX = -150.0f;
};

// ---------------------------------------------------------------------------------

class Ninja : public Object
{
enum class StateNinja { IDLE, RUN, ATTACK, JUMP, FALL, LAND, CLIMB, JUMPATTACK, FALLATTACK };

private:
    TileSet* ninjaSet;           // folha de sprites do carro
    Animation* ninjaAni;         // anima��o do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = -200.0f;              // velocidade do carro
    float speedY = 0.0f;              // velocidade do carro
    stringstream text;          // exibi��o de texto
    //Timer timerJump;            //controla tempo do pulo
   // bool releaseTimerJump = false; //controla libera��o do timer do pulo, true significa que pode disparar pulo
    //float initYJump = 0.0f;
    bool onBlock = false; //verifica se est� num bloco na itera��o
    StateNinja stateNinja = StateNinja::LAND;
    const float gravity = 1.0f;//gravidade que fica puxando player 100% do tempo para baixo.
    //mais suave por causa da resist�ncia do ar
    
public:
    //p�blico para o jogo ter acesso
    ThrowKunai* throwKunai = nullptr;//vari�vel para a cena ver se tem kunai para ser lan�ada

    Ninja(float posX);                   // construtor
    ~Ninja();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colis�es do objeto
};

// ---------------------------------------------------------------------------------

#endif