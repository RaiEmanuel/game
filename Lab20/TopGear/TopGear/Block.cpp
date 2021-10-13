#include "Block.h"
#include "WarriorAdventure.h"

// ---------------------------------------------------------------------------------
Block::Block(TypeBlock typeBlock, float posX) {
    switch (typeBlock) {
    case UNIQUE:
        spriteBlock = new Sprite("Resources/block-unique.png");
        width = 160;
        break;
    case TWO:
        spriteBlock = new Sprite("Resources/block-double.png");
        width = 240;
        break;
    case SMALL:
        spriteBlock = new Sprite("Resources/block-small.png");
        width = 240;
        break;
    case MEDIUM:
        spriteBlock = new Sprite("Resources/block-medium.png");
        width = 480;
        break;
    case LARGE:
        spriteBlock = new Sprite("Resources/block-long.png");
        width = 1400;
        break;
    }
    
    // cria bounding box
    //BBox(new Rect(-1*spriteBlock->Width()/2.0f, spriteBlock->Width() / 2.0f, -1*spriteBlock->Height() / 2.0f, spriteBlock->Height() / 2.0f));
    BBox(new Rect(
        -1 * float(spriteBlock->Width()) / 2.0f,
        -1 * float(spriteBlock->Height()) / 2.0f,
        spriteBlock->Width() / 2.0f,
        spriteBlock->Height() / 2.0f)
    );
    /*BBox(new Rect(
        -1 * float(spriteBlock->Width()) / 2.0f,
        -1 * float(spriteBlock->Height()) / 2.0f,
        spriteBlock->Width() / 2.0f,
        //spriteBlock->Height() / 2.0f)
        -1 * float(spriteBlock->Height()) / 2.0f + 1.0f)
    );*/

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    MoveTo(posX, window->Height() - spriteBlock->Height() / 2.0f);
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
    Translate(-100.0f * gameTime, 0.0f);
    //1000 porque é metade da image
    //if (X() <= 0.0f) MoveTo(window->Width(), window->CenterY());

}

// -------------------------------------------------------------------------------

void Block::Draw()
{
    spriteBlock->Draw(X(), Y(), Layer::LOWER);
}

// -------------------------------------------------------------------------------