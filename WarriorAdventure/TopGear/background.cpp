#include "background.h"


// ---------------------------------------------------------------------------------
Background::Background(){
    spriteBackground = new Sprite("Resources/background.png");
   
    MoveTo(speedX * gameTime, 400.0f);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete spriteBackground;
}

// ---------------------------------------------------------------------------------

void Background::Update()
{
    Translate(-300.0f * gameTime, 0.0f);
    //1000 porque é metade da image
    if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));

}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    spriteBackground->Draw(X(), Y(),Layer::BACK);
}

// -------------------------------------------------------------------------------