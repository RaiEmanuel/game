
#ifndef _WARRIORADVENTURE_H_
#define _WARRIORADVENTURE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Scene.h"
#include "Audio.h"
#include "Resources.h"
#include "Background.h"
#include "Player.h"
#include "Block.h"
#include <fstream>

// ------------------------------------------------------------------------------

//enum SoundIds { MUSIC, ENGINE, COLLISION };
enum ObjectTypes {PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE};
// ------------------------------------------------------------------------------

class WarriorAdventure : public Game
{
private:
    Scene* scene = nullptr;            // gerenciador de cena
    Background * background = nullptr;
    Player * player = nullptr;
    Block **  ppBlock = nullptr;//ponteiro de ponteiro porque a engina n�o aceita vetores, mas apenas objetos �nicos. 
    //Os ponteiros desse ppBlock v�o ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.
    std::ifstream fin;
    
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