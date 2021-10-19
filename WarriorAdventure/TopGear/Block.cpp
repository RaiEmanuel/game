#include "Block.h"
#include "WarriorAdventure.h"

// ---------------------------------------------------------------------------------
Block::Block(TypeBlock typeBlock, float posX, float posY) {
    switch (typeBlock) {
    case TypeBlock::UNIQUE:
        spriteBlock = new Sprite("Resources/block-unique.png");
        width = 160;
        break;
    case TypeBlock::TWO:
        spriteBlock = new Sprite("Resources/block-double.png");
        width = 240;
        break;
    case TypeBlock::SMALL:
        spriteBlock = new Sprite("Resources/block-small.png");
        width = 240;
        break;
    case TypeBlock::MEDIUM:
        spriteBlock = new Sprite("Resources/block-medium.png");
        width = 480;
        break;
    case TypeBlock::LARGE:
        spriteBlock = new Sprite("Resources/block-long.png");
        width = 1400;
        break;
    }
    
    // cria bounding box
    //BBox(new Rect(-1*spriteBlock->Width()/2.0f, spriteBlock->Width() / 2.0f, -1*spriteBlock->Height() / 2.0f, spriteBlock->Height() / 2.0f));
    BBox(new Rect(
        -1 * float(spriteBlock->Width()) / 2.0f + 45.0f,//91.0f/2 porque é a largura do player /2, ele deve ficar no limite do bloco para ficar mais realístico
        -1 * float(spriteBlock->Height()) / 2.0f,
        spriteBlock->Width() / 2.0f - 45.0f,
        spriteBlock->Height() / 2.0f)
    );

    MoveTo(posX, posY);
    type = BLOCK;
}

// ---------------------------------------------------------------------------------

Block::~Block()
{
    delete spriteBlock;
}

// ---------------------------------------------------------------------------------

void Block::Update()
{
    Translate(speedX* gameTime, 0.0f);
    //if (X() <= 0.0f) MoveTo(window->Width(), window->CenterY());
}

// -------------------------------------------------------------------------------

void Block::Draw()
{
    spriteBlock->Draw(X(), Y(), Layer::LOWER);
}

// -------------------------------------------------------------------------------