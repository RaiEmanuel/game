#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
// ------------------------------------------------------------------------------
// inicializa��o de membros est�ticos da classe
Audio* WarriorAdventure::audio = nullptr;
Scene* WarriorAdventure::scene = nullptr;

// ------------------------------------------------------------------------------
//float Block::speedX = -100.0f;
void WarriorAdventure::Init()
{
    // cria gerenciadores
    scene = new Scene();
    scene->Add(Fase_mestra::player, MOVING);
    background = new Background();
    phone = new Phone(2300,550);
    scene->Add(phone, STATIC);
    //-----------------------------
    airplane = new Airplane();
    scene->Add(airplane,STATIC);
    //-----------------------------
    loadBlocks(ppBlock);
    //-----------------------------
    scene->Add(background, STATIC);
    audio = new Audio();
    // carregar m�sicas e efeitos sonoros
    audio->Add(MUSIC, "Resources/theme2.wav");
    
    audio->Play(MUSIC, true);
   
    timerLandNewNinja.Start();
}

// ------------------------------------------------------------------------------

void WarriorAdventure::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza a cena 
    scene->CollisionDetection();
    scene->Update();

    if (Fase_mestra::player->died){
        Fase_mestra::player->died = false;
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::GAMEOVER;
        GameOver::initializedPlayer = false;
        Fase_mestra::NextLevel<GameOver>();
    }
    else if (Fase_mestra::player->win) {
        ///**********************************************
        /* ajuste para win*/
        Fase_mestra::player->win = false;
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::MENU;
        Menu::initializedPlayer = false;
        Fase_mestra::NextLevel<Menu>();
    }
    else if (window->KeyPress(VK_RETURN)) {
        ///**********************************************
        /* ajuste para win*/
        Fase_mestra::player->win = false;
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::MENU;
        Menu::initializedPlayer = false;
        Fase_mestra::NextLevel<Menu>();
    } else {
       //cria ninjas
        if (timerLandNewNinja.Elapsed(5)) {//4s lan�a novo ninja em posi��o aleat�ria da tela
            ++quantityNinjas;
            Ninja* ninja = new Ninja(float(rand() % window->Width() + window->Width()));
            scene->Add(ninja, MOVING);
            timerLandNewNinja.Reset();
        }
        /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
        /* OBSS: OTIMIZAR O FOR COMPONENTIZANDO EM FUN��O GEN�RICA  */
    }
}

// ------------------------------------------------------------------------------

void WarriorAdventure::Draw()
{
    scene->Draw();
    scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void WarriorAdventure::Finalize()
{
    delete [] ppBlock;
    //Fase_mestra::player->speedX
    scene->Remove(Fase_mestra::player, MOVING);
    delete scene;
    delete audio;
}

void WarriorAdventure::loadBlocks(Block ** ppBlock) {
    /* cria��o dos blocos pelo .txt block-position */
    std::ifstream fin;
    fin.open("Resources/block-position.txt", std::ios_base::in);
    if (!fin.is_open()) {
        //return EXIT_FAILURE;
        //erro na leitura
    }
    /* LEITURA DOS BLOCOS */
    int numBlocks; //n�mero de blocos a serem lidos
    float posX, posY; //posi��o x do bloco
    char typeBlock = 'M';//tipo do bloco
    stringstream ss;
    fin >> numBlocks;
    //esse ponteiro deleta no finalize
    ppBlock = new Block * [numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        fin >> posX >> posY >> typeBlock;
        //enum TypeBlock { UNIQUE, TWO, SMALL, MEDIUM, LARGE };
        //esses ponteiros a cena deleta
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
        WarriorAdventure::scene->Add(ppBlock[i], STATIC);//objeto deletado pela cena, apenos o ppBlock deletar manualmente
    }

    fin.close();
}


// ----------------------------------------------------------------------------


