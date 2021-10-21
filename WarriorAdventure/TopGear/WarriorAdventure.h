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
#include "Phone.h"
#include "Ninja.h"
#include "Block.h"
#include "kunai.h"
#include <fstream>
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"
#include "Boss_fight.h"
#include "Fase_mestra.h"
//CORRIGIR ENUMERA��O PARA ASSOCIADAS COM A CLASS enum class x {a,b,c};
// -----------------------------------------------------------------------------
enum SoundIds { MUSIC, ENGINE, COLLISION, PULO, FIREBALLSOUND, VENTO};//continuar
enum ObjectTypes {PLAYER, BLOCK, ZOOMBIE, NINJA, AIRPLANE, KUNAI,TIRO_AVIAO, WIND, BOSS, FIREBALL, PHONE};
// ------------------------------------------------------------------------------
class WarriorAdventure : public Game
{
public: 
    static Scene* scene;          // gerenciador de cena
private:
    Background * background = nullptr;
    Airplane* airplane = nullptr;
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    uint quantityNinjas = 0;//quantidade de ninjas que iniciam, n�o que est�o no cen�rio
    Timer timerLandNewNinja;
    Phone * phone = nullptr;
    //list<Ninja*> ninjaList;
    /* vetor ap�s testes */
    //--------------------------------------------------------------------------------
    /* Lista de Kunais para saber quais sa�ram da tela, isExit, e deletar pelo delete(* obj, static) da cena*/
    /* a cena quem ir� dar delete, ent�o remove-se dessa lista para evitar acesso indevido na pr�xima itera��o*/
    //--------------------------------------------------------------------------------
    Block ** ppBlock = nullptr;//ponteiro de ponteiro porque a engina n�o aceita vetores, mas apenas objetos �nicos. 
    //Os ponteiros desse ppBlock v�o ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.
    void loadBlocks(Block ** ppBlock);
public:
    static bool initializedPlayer;     //precisa dessa vari�vel porque o init do player � chamado apenas uma vez e precisa reinici�-lo a cada nova fase
    static Audio* audio;               // gerenciador de �udio
 
    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};
// ---------------------------------------------------------------------------------
#endif

