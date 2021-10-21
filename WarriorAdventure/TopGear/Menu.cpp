#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
#include "Menu.h"
// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe
Audio* Menu::audio = nullptr;
int Menu::fase_selecionada = 0;
bool Menu::escolha_feita = false;
Scene* Menu::scene;
Wind * Menu::ventinho = nullptr;

// ------------------------------------------------------------------------------
//float Block::speedX = -100.0f;
void Menu::Init()
{
    Fase_mestra::player->points = 0;
    escolha_feita = false;
    Menu::scene = new Scene();
    scene->Add(Fase_mestra::player, MOVING);
    background = new Sprite("Resources/Menu.png");
    //-----------------------
    buttonFase1 = new ButtonMenu("buttonLevel1.png", 800.0f, 300.0f);
    scene->Add(buttonFase1, STATIC); 
    //-----------------------
    buttonFase2 = new ButtonMenu("buttonLevel2.png", 800.0f, 380.0f);
    scene->Add(buttonFase2, STATIC);
    //-----------------------
    buttonGameOver = new ButtonMenu("buttonGameOver.png", 800.0f, 460.0f);
    scene->Add(buttonGameOver, STATIC);
    //-----------------------
    buttonWin = new ButtonMenu("buttonWin.png", 800.0f, 540.0f);
    scene->Add(buttonWin, STATIC);
    //-----------------------
    Fase_mestra::player->MoveTo(window->CenterX(), 300.0f);//garantir se no update falhar
    fase_selecionada = 0;
    audio = new Audio();
    // carregar músicas e efeitos sonoros
    audio->Add(THEME, "Resources/theme.wav");
    audio->Play(THEME, true);

    audio->Add(VENTO, "Resources/vento.wav");
}
// ------------------------------------------------------------------------------
void Menu::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
    // atualiza a cena 
        scene->Update();
        if (ventinho != nullptr) {
            switch (Fase_mestra::qual_nivel){
                case Fase_mestra::SelectedLevel::MENU:
                if (ventinho->X() > 720.0f) {
                    scene->Delete(ventinho, MOVING);
                    switch (Menu::fase_selecionada){
                    case 0:
                        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::LEVEL1;
                        WarriorAdventure::initializedPlayer = false;
                        Fase_mestra::NextLevel<WarriorAdventure>();
                        break;
                        // fase 2
                    case 1:
                        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::LEVEL2;
                        Boss_fight::initializedPlayer = false;
                        Fase_mestra::NextLevel<Boss_fight>();
                        break;
                        // game over
                    case 2:
                        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::GAMEOVER;
                        GameOver::initializedPlayer = false;
                        Fase_mestra::NextLevel<GameOver>();
                        break;
                        // win, falta fazer e linkar aqui
                    case 3:
                        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::WIN;
                        Win::initializedPlayer = false;
                        Fase_mestra::NextLevel<Win>();
                        break;
                    }
                }
                
                break;
            }
        }
 }

// ------------------------------------------------------------------------------

void Menu::Draw()
{
    background->Draw(500.0f, 300.0f, Layer::BACK);
    scene->Draw();
}

// ------------------------------------------------------------------------------

void Menu::Finalize()
{
    if (ventinho != nullptr)
        scene->Delete(ventinho, MOVING);
    ventinho = nullptr;
    delete audio;
    delete background;
    scene->Remove(Fase_mestra::player, MOVING);
    delete scene;
}
// ----------------------------------------------------------------------------