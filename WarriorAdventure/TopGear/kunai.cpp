#include "kunai.h"
#include "WarriorAdventure.h" 
// ---------------------------------------------------------------------------------
Kunai::Kunai(float posX, float posY, float velX) {
    spriteKunai = new Sprite("Resources/Kunai.png");
    speedX = velX;
    // cria bounding box
    //BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));
    // cria bounding box
    BBox(new Rect(
        -1 * float(spriteKunai->Width()) / 2.0f,
        -1 * float(spriteKunai->Height()) / 2.0f,
        float(spriteKunai->Width()) / 2.0f,
        float(spriteKunai->Height()) / 2.0f)
    );

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    MoveTo(posX, posY);
    type = KUNAI;
}
// ---------------------------------------------------------------------------------
Kunai::~Kunai()
{
    delete spriteKunai;
}
// ---------------------------------------------------------------------------------
void Kunai::Update()
{
    Translate(speedX * gameTime, 0.0f);
    //1000 porque é metade da image
    //if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));
}
// -------------------------------------------------------------------------------
void Kunai::Draw()
{
    spriteKunai->Draw(X(), Y(), Layer::FRONT);
}
// -------------------------------------------------------------------------------