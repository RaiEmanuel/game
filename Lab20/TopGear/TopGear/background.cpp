#include "background.h"


// ---------------------------------------------------------------------------------
Background::Background(){
    spriteBackground = new Sprite("Resources/background.png");
    // cria bounding box
    //BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));

    // configura posi��o do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    MoveTo(300.0f, 400.0f);
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
    //1000 porque � metade da image
    if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));

}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    spriteBackground->Draw(X(), Y(),Layer::BACK);
}

// -------------------------------------------------------------------------------