#include "Wind.h"
#include "WarriorAdventure.h" 
#include "Boss.h"
#include "Boss_fight.h"

// ---------------------------------------------------------------------------------
Wind::Wind(float posX, float posY) {
    // carrega folhas de sprites do carro
    windSet = new TileSet("Resources/wind.png", 70, 30, 5, 5);
    windAni = new Animation(windSet, 0.1f, true);//0.01f

    /*uint idle[10] = {39,38,37,36,35,34,33,32,31,30};
    uint run[10] = { 19,18,17,16,15,14,13,12,11,10 };
    uint attack[10] = { 9,8,7,6,5,4,3,2,1,0 };
    uint jump[5] = { 29,28,27,26,25 };
    uint fall[5] = { 24,23,22,21,20 };
    uint land[10] = { 49,48,47,46,45,44,43,42,41,40 };
    uint climb[10] = { 59,58,57,56,55,54,53,52,51,50 };
    uint jumpattack[5] = { 69,68,67,66,65 };
    uint fallattack[4] = { 64, 63, 62, 61 };*/

    /*ninjaAni->Add(static_cast<uint>(StateNinja::IDLE), idle, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::RUN), run, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::ATTACK), attack, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::JUMP), jump, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::FALL), fall, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::LAND), land, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::CLIMB), climb, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::JUMPATTACK), jumpattack, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::FALLATTACK), fallattack, 4);

    ninjaAni->Select(static_cast<uint>(stateNinja));*/

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
    //speedY += gravity;
    Translate(speedX * gameTime, 0.0f);
    windAni->NextFrame();
}
// -------------------------------------------------------------------------------
void Wind::Draw()
{
    windAni->Draw(X(), Y(), Layer::FRONT);
    //spriteWind->Draw(X(), Y(), Layer::FRONT, 1.0f, rotation);
}

void Wind::OnCollision(Object * obj) {
    if (obj->Type() == NINJA) {
        //WarriorAdventure::scene->Delete(obj, STATIC);
        //WarriorAdventure::ninjaList.
    }
}



// -------------------------------------------------------------------------------