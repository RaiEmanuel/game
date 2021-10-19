
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
    static Wind* ventinho;//ventinho que vai selecionar a op��o
    static Audio* audio;               // gerenciador de �udio
    static bool initializedPlayer;     //precisa dessa vari�vel porque o init do player � chamado apenas uma vez e precisa reinici�-lo a cada nova fase
    void Init();                       // inicializa��o
    void Update();                     // atualiza��o
    void Draw();                       // desenho
    void Finalize();                   // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif