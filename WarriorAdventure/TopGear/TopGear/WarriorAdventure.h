
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
#include "Ninja.h"
#include "Block.h"
#include "kunai.h"
#include <fstream>
#include <list>

// ------------------------------------------------------------------------------

enum SoundIds { MUSIC, ENGINE, COLLISION };//continuar
enum ObjectTypes {PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI};
// ------------------------------------------------------------------------------

class WarriorAdventure : public Game
{
private:
    Scene* scene = nullptr;            // gerenciador de cena
    Background * background = nullptr;
    Player * player = nullptr;
    /* vetor ap�s testes */
    /* Lista de Kunais para saber quais sa�ram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    uint quantityNinjas = 1;//quantidade de ninjas
    Timer timerLandNewNinja;
    list<Ninja*> ninjaList;
    /* vetor ap�s testes */
    //--------------------------------------------------------------------------------
    /* Lista de Kunais para saber quais sa�ram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    list<Kunai*> kunaisList;
    //--------------------------------------------------------------------------------
    Block **  ppBlock = nullptr;//ponteiro de ponteiro porque a engina n�o aceita vetores, mas apenas objetos �nicos. 
    //Os ponteiros desse ppBlock v�o ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.
    std::ifstream fin;
    
    //Sprite* sky = nullptr;             // desenho do c�u
    //Sprite* track = nullptr;           // desenho da pista

    //bool viewBBox = false;              // visualiza��o da bbox

public:
    static Audio* audio;               // gerenciador de �udio
    //static float speed;                 // velocidade do carro

    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif