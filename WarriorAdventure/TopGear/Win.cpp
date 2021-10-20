#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
#include "GameOver.h"
#include "Win.h"
// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe
Audio* Win::audio = nullptr;
// ------------------------------------------------------------------------------
//float Block::speedX = -100.0f;
void Win::Init()
{
    background = new Sprite("Resources/win.png");

    audio = new Audio();

    // carregar músicas e efeitos sonoros
    //audio->Add(GAMEOVERVOICE, "Resources/gameovervoice.wav");
    //audio->Add(GAMEOVERTHEME, "Resources/gameovertheme.wav");

    //audio->Play(GAMEOVERTHEME, true);
    //audio->Play(GAMEOVERVOICE, false);
    fontezinha = new Font("Resources/Fonte1.png");
    fontezinha->Spacing("Resources/Fonte1.dat");
}
// ------------------------------------------------------------------------------
void Win::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_RETURN)) {
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::MENU;
        Menu::initializedPlayer = false;
        Fase_mestra::NextLevel<Menu>();
    }
}
// ------------------------------------------------------------------------------
void Win::Draw()
{
    background->Draw(500.0f, 300.0f, Layer::FRONT);
    stringstream ss;
    ss << Fase_mestra::player->points << "    N i n j a ( s )" << std::endl;
    fontezinha->Draw(510.0f, 530.0f, ss.str().c_str(), {1,1,1,1},Layer::FRONT,0.8f);
}
// ------------------------------------------------------------------------------
void Win::Finalize()
{
    delete audio;
    delete background;
}
// ----------------------------------------------------------------------------

