#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
#include "GameOver.h"
// ------------------------------------------------------------------------------
// inicializa��o de membros est�ticos da classe

Audio* GameOver::audio = nullptr;

// ------------------------------------------------------------------------------
//float Block::speedX = -100.0f;
void GameOver::Init()
{
    background = new Sprite("Resources/gameover.png");
   
    audio = new Audio();

    // carregar m�sicas e efeitos sonoros
    audio->Add(GAMEOVERVOICE, "Resources/gameovervoice.wav");
    audio->Add(GAMEOVERTHEME, "Resources/gameovertheme.wav");
  
   
    audio->Play(GAMEOVERTHEME, true);
    audio->Play(GAMEOVERVOICE, false);
}

// ------------------------------------------------------------------------------

void GameOver::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    
    if (window->KeyPress(VK_RETURN)) {
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::MENU;
        Fase_mestra::NextLevel<Menu>();
    }
  

}
// ------------------------------------------------------------------------------

void GameOver::Draw()
{
    background->Draw(500.0f, 300.0f, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void GameOver::Finalize()
{
    
    delete audio;
    delete background;
}


// ----------------------------------------------------------------------------

