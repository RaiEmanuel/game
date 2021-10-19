#include "Bola_de_fogo.h"
#include "Boss_fight.h"
#include "Boss.h"
#include "WarriorAdventure.h"
// ---------------------------------------------------------------------------------
Bola_de_fogo::Bola_de_fogo(float posX, float posY, float velX) {
    bola_de_fogoSet = new TileSet("Resources/fire.png", 49, 40, 5, 5);
    bola_de_fogoAni = new Animation(bola_de_fogoSet, 0.1f, true);//0.01f
    speedX = velX;
    // cria bounding box
    //BBox(new Rect(-80.0f, -40.0f, 80.0f, 48.0f));
    // cria bounding box

    BBox(new Rect(
        -1 * float(bola_de_fogoSet->TileWidth()) / 2.0f,
        -1 * float(bola_de_fogoSet->TileHeight()) / 2.0f,
        float(bola_de_fogoSet->TileWidth()) / 2.0f,
        float(bola_de_fogoSet->TileHeight()) / 2.0f)
    );

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    MoveTo(posX, posY);
    type = FIREBALL;
}
// ---------------------------------------------------------------------------------
Bola_de_fogo::~Bola_de_fogo()
{
    delete bola_de_fogoAni;
    delete bola_de_fogoSet;
}
// ---------------------------------------------------------------------------------
void Bola_de_fogo::Update()
{
    Translate(speedX * gameTime, 0.0f);

    if (X() + float(bola_de_fogoSet->TileWidth()) / 2.0f <= 0)
    {
        //OutputDebugString("Deletando kunai da cena e do jogo");
        isExit = true;
    }
    //1000 porque é metade da image
    //if (X() <= 0.0f) MoveTo(float(window->Width()), float(window->CenterY()));

}
// -------------------------------------------------------------------------------
void Bola_de_fogo::Draw()
{
    bola_de_fogoAni->Draw(X(), Y(), Layer::FRONT);
}
// -------------------------------------------------------------------------------