
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Resources.h"
#include "Background.h"
#include "Player.h"
#include "Ninja.h"
#include "Block.h"
#include "kunai.h"
#include <fstream>
#include <list>
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"
#include "Boss.h"


// ------------------------------------------------------------------------------

//enum SoundIds { MUSIC, ENGINE, COLLISION };//continuar
//enum ObjectTypes { PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI, TIRO_AVIAO, WIND, BOSS };

enum Musics { GAMEOVERVOICE, GAMEOVERTHEME };//continuar


// ------------------------------------------------------------------------------

class GameOver : public Game
{

public: 
    //static Scene* scene;          // gerenciador de cena

private:
    Sprite * background = nullptr;


public:
    static Audio* audio;               // gerenciador de áudio

    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif