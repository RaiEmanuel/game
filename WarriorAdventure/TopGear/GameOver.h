
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
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"
#include "Boss.h"
// ------------------------------------------------------------------------------
enum Musics { GAMEOVERVOICE, GAMEOVERTHEME };//continuar
// ------------------------------------------------------------------------------
class GameOver : public Game
{
public: 
    //static Scene* scene;          // gerenciador de cena
    static bool initializedPlayer;     //precisa dessa variável porque o init do player é chamado apenas uma vez e precisa reiniciá-lo a cada nova fase
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