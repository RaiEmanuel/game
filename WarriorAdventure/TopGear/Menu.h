
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


// ------------------------------------------------------------------------------

//enum SoundIds { MUSIC, ENGINE, COLLISION };//continuar
//enum ObjectTypes { PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI, TIRO_AVIAO, WIND, BOSS };

enum MusicsMenu { THEME };//continuar


// ------------------------------------------------------------------------------

class Menu : public Game
{

public:
    //static Scene* scene;          // gerenciador de cena

private:
    Sprite* background = nullptr;
    ButtonMenu* buttonFase1 = nullptr, 
        * buttonFase2 = nullptr,
        * buttonGameOver = nullptr;


public:
    static Audio* audio;               // gerenciador de áudio

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif