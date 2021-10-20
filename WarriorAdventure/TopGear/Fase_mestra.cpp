#include "Engine.h"
#include "Fase_mestra.h"
#include "WarriorAdventure.h"
#include "Boss_fight.h"

// inicializa membros estáticos da classe
Game* Fase_mestra::level = nullptr;
Player* Fase_mestra::player = nullptr;
Audio* Fase_mestra::audio = nullptr;
bool    Fase_mestra::viewBBox = false;
Fase_mestra::SelectedLevel Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::WIN;
bool Menu::initializedPlayer = false;
bool WarriorAdventure::initializedPlayer = false;
bool Boss_fight::initializedPlayer = false;
bool GameOver::initializedPlayer = false;
bool Win::initializedPlayer = false;
//listas
// ------------------------------------------------------------------------------
void Fase_mestra::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    // bounding box não visível
    viewBBox = false;
    // cria jogador
    player = new Player();
    switch (Fase_mestra::qual_nivel)
    {
    case Fase_mestra::SelectedLevel::MENU:
        level = new Menu();
        break;
    case Fase_mestra::SelectedLevel::LEVEL1:
        level = new WarriorAdventure();
        break;
    case Fase_mestra::SelectedLevel::LEVEL2:
        level = new Boss_fight();
        break;
    case Fase_mestra::SelectedLevel::WIN:
        level = new GameOver();
        break;
    case Fase_mestra::SelectedLevel::GAMEOVER:
        level = new GameOver();
        break;
    }
    level->Init();
}

// ------------------------------------------------------------------------------

void Fase_mestra::Update()
{
    // atualiza nível
    level->Update();
}

// ------------------------------------------------------------------------------

void Fase_mestra::Draw()
{
    // desenha nível
    level->Draw();
}

// ------------------------------------------------------------------------------

void Fase_mestra::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1000, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Warrior Adventure");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::MENU;
    int status = engine->Start(new Fase_mestra());
    

    delete engine;
    return status;
}


// ----------------------------------------------------------------------------

