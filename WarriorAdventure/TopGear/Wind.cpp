#include "Wind.h"
#include "WarriorAdventure.h" 
#include "Boss.h"
#include "Boss_fight.h"

// ---------------------------------------------------------------------------------
Wind::Wind(float posX, float posY) {
    // carrega folhas de sprites do carro
    windSet = new TileSet("Resources/wind.png", 70, 30, 5, 5);
    windAni = new Animation(windSet, 0.1f, true);//0.01f

    BBox(new Rect(
        -1 * float(windSet->TileWidth()) / 2.0f,
        -1 * float(windSet->TileHeight()) / 2.0f,
        float(windSet->TileWidth()) / 2.0f,
        float(windSet->TileHeight()) / 2.0f)
    );

    // configura posição do objeto
    //MoveTo(window->CenterX(), window->CenterY() + 200.0f);
    //ajusta local do tiro sair
    MoveTo(posX + float(windSet->TileWidth())/2.0f, posY);
    type = WIND;
}
// ---------------------------------------------------------------------------------
Wind::~Wind()
{
    delete windSet;
    delete windAni;
}
// ---------------------------------------------------------------------------------
void Wind::Update()
{
    Translate(speedX * gameTime, 0.0f);
    windAni->NextFrame();
    
}
// -------------------------------------------------------------------------------
void Wind::Draw()
{
    windAni->Draw(X(), Y(), Layer::FRONT);
}

void Wind::OnCollision(Object * obj) {
    if (obj->Type() == NINJA) {
        Fase_mestra::player->points++;
    }
}



// -------------------------------------------------------------------------------