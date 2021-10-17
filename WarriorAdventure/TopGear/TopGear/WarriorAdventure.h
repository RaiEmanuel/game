
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
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"

// ------------------------------------------------------------------------------

enum SoundIds { MUSIC, ENGINE, COLLISION };//continuar
enum ObjectTypes {PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI,TIRO_AVIAO, WIND};
// ------------------------------------------------------------------------------

class WarriorAdventure : public Game
{

public: static Scene* scene;          // gerenciador de cena

private:
    
    Background * background = nullptr;
    Player * player = nullptr;
    Airplane* airplane = nullptr;
    /* vetor após testes */
    /* Lista de Kunais para saber quais saíram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem irá dar delete, então remove-se dessa lista para evitar acesso indevido na próxima iteração*/
    uint quantityNinjas = 0;//quantidade de ninjas que iniciam, não que estão no cenário
    Timer timerLandNewNinja;
    list<Ninja*> ninjaList;
    /* vetor após testes */
    //--------------------------------------------------------------------------------
    /* Lista de Kunais para saber quais saíram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem irá dar delete, então remove-se dessa lista para evitar acesso indevido na próxima iteração*/
    list<Kunai*> kunaisList;
    //--------------------------------------------------------------------------------
    Block **  ppBlock = nullptr;//ponteiro de ponteiro porque a engina não aceita vetores, mas apenas objetos únicos. 
    //Os ponteiros desse ppBlock vão ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.
    
    std::ifstream fin;
    
    //Sprite* sky = nullptr;             // desenho do céu
    //Sprite* track = nullptr;           // desenho da pista

    //bool viewBBox = false;              // visualização da bbox

public:
    static Audio* audio;               // gerenciador de áudio
    //static float speed;                 // velocidade do carro
    static list<Tiro_aviao*> engineList;
    static list<Wind*> windList;
    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif