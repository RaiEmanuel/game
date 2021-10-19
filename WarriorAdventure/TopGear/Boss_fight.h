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
#include "Airplane.h"
#include "Tiro_aviao.h"
#include "Wind.h"
#include "Background_boss_fight.h"
#include "Boss.h"

// ------------------------------------------------------------------------------

enum Musicas_boss_fight_id { WIDE};//continuar
 
// ------------------------------------------------------------------------------

class Boss_fight : public Game
{

public: static Scene* scene;          // gerenciador de cena
private:
    Background_boss_fight* background_boss_fight = nullptr;
    Boss* boss = nullptr;
    Block** ppBlock = nullptr;//ponteiro de ponteiro porque a engina não aceita vetores, mas apenas objetos únicos. 
    //Os ponteiros desse ppBlock vão ser colocados na cena como objetos normais para ela deletar quando adequado. 
    //ppBlock fica a cargo do programador. LEMBRAR DE DELETAR NO FIM.
    std::ifstream fin;
    Timer medidor;
public:
    static bool initializedPlayer;     //precisa dessa variável porque o init do player é chamado apenas uma vez e precisa reiniciá-lo a cada nova fase
    static Audio* audio;               // gerenciador de áudio
    static bool chefe_derrotado;
    
    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ---------------------------------------------------------------------------------

#endif