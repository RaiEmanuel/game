#include "Phone.h"
#include "WarriorAdventure.h"

// ---------------------------------------------------------------------------------
Phone::Phone(float posX, float posY) {
    spritePhone = new Sprite("Resources/phone.png");
    // cria bounding box
    //BBox(new Rect(-1*spritePhone->Width()/2.0f, spritePhone->Width() / 2.0f, -1*spritePhone->Height() / 2.0f, spritePhone->Height() / 2.0f));
    BBox(new Rect(-14,-50,14,50));

    MoveTo(posX, posY);
    type = PHONE;
}

// ---------------------------------------------------------------------------------

Phone::~Phone()
{
    delete spritePhone;
}

void Phone::Update()
{
    Translate(-100.0f * gameTime, 0.0f);
}

void Phone::Draw()
{
    spritePhone->Draw(X(), Y(), Layer::FRONT, scale, rotation);
}

// -------------------------------------------------------------------------------