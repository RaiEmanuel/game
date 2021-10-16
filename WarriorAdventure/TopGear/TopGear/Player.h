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
class Player : public Object
{
    enum class StatePlayer { IDLE, RUN, ATTACK, JUMP, FALL };
private:
    TileSet * playerSet;           // folha de sprites do carro
    Animation * playerAni;         // anima��o do carro
    //Font * speedFont;           // fonte para exibir a velocidade
    float speedX = 300.0f;              // velocidade do carro
    float speedY = 0.0f;              // velocidade do carro
    stringstream text;          // exibi��o de texto
    bool died = false;
    bool onBlock = false; //verifica se est� num bloco na itera��o
    Player::StatePlayer statePlayer = StatePlayer::FALL;
    const float gravity = 50.0f;//gravidade que fica puxando player 100% do tempo para baixo
public:
    Player();                   // construtor
    ~Player();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
    void OnCollision(Object * obj);                // colis�es do objeto
}; 

// ---------------------------------------------------------------------------------

#endif