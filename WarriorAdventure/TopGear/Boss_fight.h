
#ifndef _BOSS_FIGHT_H_
#define _BOSS_FIGHT_H_

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
#include "Background_boss_fight.h"
#include "Boss.h"


// ------------------------------------------------------------------------------

//enum SoundIds { MUSIC, ENGINE, COLLISION };//continuar
//enum ObjectTypes { PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI, TIRO_AVIAO, WIND, BOSS };

enum Musicas_boss_fight_id { WIDE};//continuar

 
// ------------------------------------------------------------------------------

class Boss_fight : public Game
{

public: static Scene* scene;          // gerenciador de cena

private:

    Background_boss_fight* background_boss_fight = nullptr;
    Player* player = nullptr;
    Boss* boss = nullptr;
    //Airplane* airplane = nullptr;
    /* vetor ap�s testes */
    /* Lista de Kunais para saber quais sa�ram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    //uint quantityNinjas = 0;//quantidade de ninjas que iniciam, n�o que est�o no cen�rio
    //Timer timerLandNewNinja;
    //list<Ninja*> ninjaList;
    /* vetor ap�s testes */
    //--------------------------------------------------------------------------------
    /* Lista de Kunais para saber quais sa�ram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    //list<Kunai*> kunaisList;
    //--------------------------------------------------------------------------------
    Block** ppBlock = nullptr;//ponteiro de ponteiro porque a engina n�o aceita vetores, mas apenas objetos �nicos. 
    //Os ponteiros desse ppBlock v�o ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.

    std::ifstream fin;

    //Sprite* sky = nullptr;             // desenho do c�u
    //Sprite* track = nullptr;           // desenho da pista

    //bool viewBBox = false;              // visualiza��o da bbox

    Timer medidor;


public:
    static Audio* audio;               // gerenciador de �udio
    //static float speed;                 // velocidade do carro
   // static list<Tiro_aviao*> engineList;
    static list<Wind*> windList2;
    static bool chefe_derrotado;
    
    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif