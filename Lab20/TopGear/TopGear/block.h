
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

enum TypeBlock { UNIQUE, TWO, SMALL, MEDIUM, LARGE };

// ---------------------------------------------------------------------------------

class Block : public Object
{
private:
    Sprite* spriteBlock = nullptr; //cena de fundo que corre para tr�s
    TypeBlock typeBlock;
public:
    float width = 0.0f;///corrigir com solu��o menos gambiarra. Precis-se da largura do bloco.
    Block(TypeBlock typeBlock, float posX);                   // construtor
    ~Block();                  // destrutor

    void Update();              // atualiza estado do objeto
    void Draw();                // desenha objeto
};

// ---------------------------------------------------------------------------------

#endif         