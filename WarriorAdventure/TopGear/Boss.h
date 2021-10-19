#ifndef _BOSS_H_
#define _BOSS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
#include "TileSet.h"             // folha de sprites
#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 

#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

struct ThrowTiro {
    float posX = 500.0f;
    float posY = 500.0f;
    float velX = -150.0f;
};

// ---------------------------------------------------------------------------------

class Boss : public Object
{
    enum class StateBoss { IDLE, SHOOT,EXPLOSION, INPUT_TELEPORTATION, EXIT_TELEPORTATION };

private:
    TileSet* bossSet;           // folha de sprites do carro
    Animation* bossAni;         // anima��o do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    //float speedX = -200.0f;              // velocidade do carro
    //float speedY = 0.0f;              // velocidade do carro
    stringstream text;          // exibi��o de texto
    //Timer timerJump;            //controla tempo do pulo
   // bool releaseTimerJump = false; //controla libera��o do timer do pulo, true significa que pode disparar pulo
    //float initYJump = 0.0f;
    //bool onBlock = false; //verifica se est� num bloco na itera��o
    //StateNinja stateNinja = StateNinja::LAND;
    //const float gravity = 1.0f;//gravidade que fica puxando player 100% do tempo para baixo.
    //mais suave por causa da resist�ncia do ar
    StateBoss stateBoss = StateBoss::IDLE;
    Timer temporizador;
public:
    //p�blico para o jogo ter acesso
    ThrowTiro* throwTiro = nullptr;//vari�vel para a cena ver se tem kunai para ser lan�ada
    int qual_bloco_esta;                // 1 - cima, 2 - baixo
    int tiros_tomados;
    int tiros_necessarios_para_morrer;
    bool atingivel;
    Boss();                   // construtor
    ~Boss();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object* obj);                // colis�es do objeto
    void teletransporte();
};

// ---------------------------------------------------------------------------------

#endif