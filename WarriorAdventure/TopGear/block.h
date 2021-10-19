
#ifndef _BLOCK_H_
#define _BLOCK_H_

// ---------------------------------------------------------------------------------

#include "Object.h"              // objetos do jogo
//#include "TileSet.h"             // folha de sprites
//#include "Animation.h"           // anima��o de sprites
#include "Types.h"               // tipos espec�ficos do motor
#include "Font.h"                // desenho de texto 
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------

class Block : public Object
{    
private:
    Sprite* spriteBlock = nullptr; //cena de fundo que corre para tr�s
    
public:
    enum class TypeBlock { UNIQUE, TWO, SMALL, MEDIUM, LARGE };
    TypeBlock typeBlock;
    float width = 0.0f;///corrigir com solu��o menos gambiarra. Precis-se da largura do bloco.
    static float speedX;
    Block(TypeBlock typeBlock, float posX, float posY);                   // construtor
    ~Block();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         