#include "Tiro_aviao.h"
#include "WarriorAdventure.h" 
// ---------------------------------------------------------------------------------
Tiro_aviao::Tiro_aviao(float posX, float posY) {
    spriteTiro_aviao = new Sprite("Resources/engine.png");
    
    // cria bounding box
    //BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));
    // cria bounding box
    BBox(new Rect(
        -1 * float(spriteTiro_aviao->Width()) / 2.0f,
        -1 * float(spriteTiro_aviao->Height()) / 2.0f,
        float(spriteTiro_aviao->Width()) / 2.0f,
        float(spriteTiro_aviao->Height()) / 2.0f)
    );

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    MoveTo(posX, posY);
    type = TIRO_AVIAO;
}
// ---------------------------------------------------------------------------------
Tiro_aviao::~Tiro_aviao()
{
    delete spriteTiro_aviao;
}
// ---------------------------------------------------------------------------------
void Tiro_aviao::Update()
{
    speedY += gravity;
    Translate( speedX * gameTime, speedY * gameTime);
    

    //if (Y() + float(spriteTiro_aviao->Width()) / 2.0f >= window->Width())
    //{
        //OutputDebugString("Deletando kunai da cena e do jogo");
     //   WarriorAdventure::scene->Delete();
    //}
    //1000 porque é metade da image
    //if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));

}
// -------------------------------------------------------------------------------
void Tiro_aviao::Draw()
{
    spriteTiro_aviao->Draw(X(), Y(), Layer::FRONT);
}
// -------------------------------------------------------------------------------