#include "Background_boss_fight.h"


// ---------------------------------------------------------------------------------
Background_boss_fight::Background_boss_fight() {
    spriteBackground_boss_fight = new Sprite("Resources/volcano.png");
    // cria bounding box
    //BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    //MoveTo(speedX * gameTime, 400.0f);
}

// ---------------------------------------------------------------------------------

Background_boss_fight::~Background_boss_fight()
{
    delete spriteBackground_boss_fight;
}

// ---------------------------------------------------------------------------------

void Background_boss_fight::Update()
{
    //Translate(-100.0f * gameTime, 0.0f);
    //1000 porque é metade da image
    //if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));

}

// -------------------------------------------------------------------------------

void Background_boss_fight::Draw()
{
    spriteBackground_boss_fight->Draw(X(), Y(), Layer::BACK);
}

// -------------------------------------------------------------------------------