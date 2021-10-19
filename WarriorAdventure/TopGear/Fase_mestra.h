
#ifndef _FASE_MESTRA_H_
#define _FASE_MESTRA_H_

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"
#include "GameOver.h"
#include "Menu.h"
#include "Phone.h"

// ------------------------------------------------------------------------------
//enum Sounds { MENU, MUSIC, TRANSITION };
// ------------------------------------------------------------------------------
class Fase_mestra : public Game
{
    
private:
    static Game* level;            // nível atual do jogo
public:
    enum class SelectedLevel { MENU, LEVEL1, LEVEL2, GAMEOVER, WIN };
    static Player* player;         // jogador 
    static Audio* audio;           // sistema de áudio
    static bool viewBBox;           // estado da bounding box
    static Fase_mestra::SelectedLevel qual_nivel;               // 0 - home, 1 - 1ªfase, 2 - 2ªfase, 3 - game over

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif