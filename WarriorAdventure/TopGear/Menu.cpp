#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
#include "Menu.h"
// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

Audio* Menu::audio = nullptr;

// ------------------------------------------------------------------------------
//float Block::speedX = -100.0f;
void Menu::Init()
{
    background = new Sprite("Resources/Menu.png");
    buttonFase1 = new ButtonMenu("buttonLevel1.png", 800.0f, 310.0f);
    buttonFase2 = new ButtonMenu("buttonLevel2.png", 800.0f, 410.0f);
    buttonGameOver = new ButtonMenu("buttonGameOver.png", 800.0f, 510.0f);

    audio = new Audio();

    // carregar músicas e efeitos sonoros
    audio->Add(THEME, "Resources/theme.wav");

    
    audio->Play(THEME, true);
}

// ------------------------------------------------------------------------------

void Menu::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena 
    
    if (window->KeyPress(VK_RETURN)) {
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::LEVEL1;
        Fase_mestra::NextLevel<WarriorAdventure>();
    }


}
// ------------------------------------------------------------------------------

void Menu::Draw()
{
    
    background->Draw(500.0f, 300.0f, Layer::BACK);
    buttonFase1->Draw();
    buttonFase2->Draw();
    buttonGameOver->Draw();
}

// ------------------------------------------------------------------------------

void Menu::Finalize()
{
    delete audio;
    delete background;
    delete buttonFase1;
    delete buttonFase2;
    delete buttonGameOver;
}


// ----------------------------------------------------------------------------

