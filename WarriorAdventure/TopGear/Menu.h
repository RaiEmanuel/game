
#ifndef _MENU_H_
#define _MENU_H_
// ---------------------------------------------------------------------------------
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Resources.h"
#include "Player.h"
#include "ButtonMenu.h"
#include "Fase_mestra.h"
#include "Engine.h"
// ------------------------------------------------------------------------------
enum MusicsMenu { THEME };//continuar
// ------------------------------------------------------------------------------
class Menu : public Game
{
//public: static Scene* scene;          // gerenciador de cena
public:
    static Scene* scene;          // gerenciador de cena
    static int fase_selecionada;
    static bool escolha_feita;
private:
    Sprite* background = nullptr;
    ButtonMenu* buttonFase1 = nullptr, 
        * buttonFase2 = nullptr,
        * buttonGameOver = nullptr,
        *buttonWin = nullptr;
    
public:
    static Wind* ventinho;//ventinho que vai selecionar a opção
    static Audio* audio;               // gerenciador de áudio
    static bool initializedPlayer;     //precisa dessa variável porque o init do player é chamado apenas uma vez e precisa reiniciá-lo a cada nova fase
    void Init();                       // inicialização
    void Update();                     // atualização
    void Draw();                       // desenho
    void Finalize();                   // finalização
};

// ---------------------------------------------------------------------------------

#endif