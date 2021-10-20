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
//boss_fight
bool Boss_fight::chefe_derrotado = false;

// ------------------------------------------------------------------------------

void Boss_fight::Init()
{
    // cria gerenciadores
    scene = new Scene();
    background_boss_fight = new Background_boss_fight();
    Fase_mestra::player->MoveTo(window->CenterX()-80, 0.0f);
    
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
    scene->Add(Fase_mestra::player, MOVING);
    chefe_derrotado = false;
    scene->Add(boss, STATIC);
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
        GameOver::initializedPlayer = false;
        Fase_mestra::NextLevel<GameOver>();
    }
    else
    {
        if (chefe_derrotado) {
            Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::WIN;
            /**************************************/
            /*******  CORRIGIR PARA CLASSE WIN ****/
            /**************************************/
            Win::initializedPlayer = false;
            Fase_mestra::player->throwWind = true;
            Fase_mestra::NextLevel<Win>();
        }
        else if (Fase_mestra::player->died) {
            Fase_mestra::player->throwWind = true;
            Fase_mestra::player->died = false;
            Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::GAMEOVER;
            GameOver::initializedPlayer = false;
            Fase_mestra::NextLevel<GameOver>();
        }
        else {
            /* OBSS: OTIMIZAR O FOR COMPONENTIZANDO EM FUNÇÃO GENÉRICA  */
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
}
// ------------------------------------------------------------------------------
void Boss_fight::Draw()
{
    // desenha a cena
    scene->Draw();
    scene->DrawBBox();
}
// ------------------------------------------------------------------------------
void Boss_fight::Finalize()
{
    Fase_mestra::player->died = false;
    scene->Remove(Fase_mestra::player, MOVING);
    Boss_fight::initializedPlayer = false;
    delete scene;
    delete [] ppBlock;
    delete audio;
}
// ----------------------------------------------------------------------------