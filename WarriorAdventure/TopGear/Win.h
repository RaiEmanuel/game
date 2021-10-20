
#ifndef _WIN_H_
#define _WIN_H_
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
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"
#include "Boss.h"
// ------------------------------------------------------------------------------
//enum Musics { GAMEOVERVOICE, GAMEOVERTHEME };//continuar
// ------------------------------------------------------------------------------
class Win : public Game
{
public:
    //static Scene* scene;          // gerenciador de cena
    static bool initializedPlayer;     //precisa dessa vari�vel porque o init do player � chamado apenas uma vez e precisa reinici�-lo a cada nova fase
private:
    Sprite* background = nullptr;
    Font* fontezinha = nullptr;
public:
    static Audio* audio;               // gerenciador de �udio

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif