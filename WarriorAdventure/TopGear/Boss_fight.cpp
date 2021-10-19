#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
#include "Boss_fight.h"
#include "Background_boss_fight.h"
// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

Audio* Boss_fight::audio = nullptr;
Scene* Boss_fight::scene = nullptr;
//list<Tiro_aviao*> Boss_fight::engineList;
list<Wind*> Boss_fight::windList2;
bool Boss_fight::chefe_derrotado = false;

// ------------------------------------------------------------------------------

void Boss_fight::Init()
{
    Block::speedX = 0.0f;
    // cria gerenciadores
    scene = new Scene();
    background_boss_fight = new Background_boss_fight();
    //player = new Player();
    Fase_mestra::player->MoveTo(window->CenterX()-80, 0.f);
    
    boss = new Boss();
    medidor.Start();
   
    /* criação dos blocos pelo .txt block-position */
    fin.open("Resources/block-position_boss_fight.txt", std::ios_base::in);
    if (!fin.is_open()) {
        //return EXIT_FAILURE;
        //erro na leitura
    }
    /* LEITURA DOS BLOCOS */
    int numBlocks; //número de blocos a serem lidos
    float posX, posY; //posição x do bloco
    char typeBlock = 'M';//tipo do bloco
    stringstream ss;
    fin >> numBlocks;
    //ss << "xxxxxxxxxxxxxxx lidos y blocos = " << numBlocks<<std::endl;
    //OutputDebugString(ss.str().c_str());
    ppBlock = new Block * [numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        fin >> posX >> posY >> typeBlock;
        //enum TypeBlock { UNIQUE, TWO, SMALL, MEDIUM, LARGE };
        switch (typeBlock) {
        case 'U':
            ppBlock[i] = new Block(Block::TypeBlock::UNIQUE, posX, posY);
            break;
        case 'T':
            ppBlock[i] = new Block(Block::TypeBlock::TWO, posX, posY);
            break;
        case 'S':
            ppBlock[i] = new Block(Block::TypeBlock::SMALL, posX, posY);
            break;
        case 'M':
            ppBlock[i] = new Block(Block::TypeBlock::MEDIUM, posX, posY);
            break;
        case 'L':
            ppBlock[i] = new Block(Block::TypeBlock::LARGE, posX, posY);
            break;
        }
        ppBlock[i]->speedX = 0;
        scene->Add(ppBlock[i], STATIC);//objeto deletado pela cena, apenos o ppBlock deletar manualmente
    }

    fin.close();
    //adição na cena
    background_boss_fight->MoveTo(background_boss_fight->X() + window->Width()/2, background_boss_fight->Y()+window->Height()/2);
    scene->Add(background_boss_fight, STATIC);
    scene->Add(Fase_mestra::Fase_mestra::player, MOVING);
    scene->Add(boss, STATIC);
    //scene->Add(ninja, MOVING);
    //scene->Add(ninja2, MOVING);
    //scene->Add(kunai, STATIC);

    audio = new Audio();

    // carregar músicas e efeitos sonoros
    audio->Add(WIDE, "Resources/wide_putin.wav");
    
    audio->Play(WIDE, true);
}

// ------------------------------------------------------------------------------

void Boss_fight::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena 
    scene->CollisionDetection();
    scene->Update();

    // atualiza a cena 
    if (window->KeyPress(VK_RETURN)) {
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::GAMEOVER;
        Fase_mestra::NextLevel<GameOver>();
    }else {
        /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    /* OBSS: OTIMIZAR O FOR COMPONENTIZANDO EM FUNÇÃO GENÉRICA  */

        for (auto i = windList2.begin(); i != windList2.end();) {
            //OBS: DELETAR LISTA NO FINALIZE
            //OutputDebugString("girooooooo");
            Wind* wind = *i;
            stringstream o;
            o << "altura do engine " << wind->X() << "altura" << window->Width() << std::endl;
            if (wind->X() - 35.0f >= window->Width()) {
                //OutputDebugString("xxxxxxxxxxxxxxxxxxxxxxx deletooooooou vento");
                //OutputDebugString(o.str().c_str());
                scene->Delete(wind, MOVING);
                windList2.erase(i);
                i = windList2.begin();
            }//30 e altura da catracaELSE
            else {
                //tiro->Rotate(-500.0f * gameTime);
                ++i;
            }

        }

        // habilita/desabilita bounding box
        //if (window->KeyPress('B'))
            //viewBBox = !viewBBox;


        if (medidor.Elapsed(6))
        {
            if (chefe_derrotado == false)
            {
                OutputDebugString("Chamou teleporte\n");
                boss->teletransporte();
            }

            medidor.Reset();
        }
    }

    

}
// ------------------------------------------------------------------------------

void Boss_fight::Draw()
{
    // desenha o pano de fundo
    //track->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    //sky->Draw(window->CenterX(), window->CenterY(), Layer::UPPER);

    // desenha a cena
    scene->Draw();

    // desenha bounding box dos objetos
    //if (viewBBox)
    scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Boss_fight::Finalize()
{
    /*delete track;
    delete sky;
    delete scene;
    delete audio;*/
    //delete ppBlock;
    //ninjaList.clear();//limpa lista de ninjas porque vão ser deletados abaixo
    //engineList.clear();
    windList2.clear();
    scene->Remove(Fase_mestra::player, MOVING);
    Block::speedX = -100.0f;
    delete scene;
    delete [] ppBlock;
    delete audio;
}


// ----------------------------------------------------------------------------

