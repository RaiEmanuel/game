#ifndef _NINJA_H_
#define _NINJA_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // animação de sprites
#include "Types.h"               // tipos específicos do motor
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
    Animation* ninjaAni;         // animação do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = -200.0f;              // velocidade do carro
    float speedY = 0.0f;              // velocidade do carro
    stringstream text;          // exibição de texto
    //Timer timerJump;            //controla tempo do pulo
   // bool releaseTimerJump = false; //controla liberação do timer do pulo, true significa que pode disparar pulo
    //float initYJump = 0.0f;
    bool onBlock = false; //verifica se está num bloco na iteração
    StateNinja stateNinja = StateNinja::LAND;
    const float gravity = 1.0f;//gravidade que fica puxando player 100% do tempo para baixo.
    //mais suave por causa da resistência do ar
    
public:
    //público para o jogo ter acesso
    ThrowKunai* throwKunai = nullptr;//variável para a cena ver se tem kunai para ser lançada

    Ninja(float posX);                   // construtor
    ~Ninja();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colisões do objeto
};

// ---------------------------------------------------------------------------------

#endif