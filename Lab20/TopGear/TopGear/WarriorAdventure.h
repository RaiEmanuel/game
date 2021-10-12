
#ifndef _WARRIORADVENTURE_H_
#define _WARRIORADVENTURE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

//enum SoundIds { MUSIC, ENGINE, COLLISION };

// ------------------------------------------------------------------------------

class WarriorAdventure : public Game
{
private:
    //Scene* scene = nullptr;            // gerenciador de cena
    //Sprite* sky = nullptr;             // desenho do c�u
    //Sprite* track = nullptr;           // desenho da pista

    //bool viewBBox = false;              // visualiza��o da bbox

public:
    //static Audio* audio;               // gerenciador de �udio
    static float speed;                 // velocidade do carro

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif