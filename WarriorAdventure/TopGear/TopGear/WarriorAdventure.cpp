/**********************************************************************************
// TopGear (Código Fonte)
//
// Criação:     11 Jul 2019
// Atualização: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Uso da escala em um jogo estilo TopGear
//
**********************************************************************************/

#include "Engine.h"
#include "WarriorAdventure.h"
//#include "Stripes.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>

//#include "Cars.h"

// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

Audio* WarriorAdventure::audio = nullptr;
//float   TopGear::speed = 1000.0f;

// ------------------------------------------------------------------------------
float Block::speedX = -100.0f;
//float Block::speedX = 0.0f;
void WarriorAdventure::Init()
{
    // cria gerenciadores
    scene = new Scene();
    background = new Background();
    player = new Player();
    for (uint i = 0; i < quantityNinjas; ++i) {
        Ninja* ninja = new Ninja(i*500.0f + 800.0f);
        scene->Add(ninja, MOVING);
        ninjaList.push_back(ninja);//adiciona ponteiro apenas para saber os ninjas da cena
    }
    //ninja = new Ninja(560);
    //ninja2 = new Ninja(700);
    
    /* criação dos blocos pelo .txt block-position */
    fin.open("Resources/block-position.txt", std::ios_base::in);
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
    ss << "xxxxxxxxxxxxxxx lidos y blocos = " << numBlocks<<std::endl;
    OutputDebugString(ss.str().c_str());
    ppBlock = new Block *[numBlocks];
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
        scene->Add(ppBlock[i], STATIC);//objeto deletado pela cena, apenos o ppBlock deletar manualmente
    }

    fin.close();
    //adição na cena
    scene->Add(background, STATIC);
    scene->Add(player, MOVING);
    //scene->Add(ninja, MOVING);
    //scene->Add(ninja2, MOVING);
    //scene->Add(kunai, STATIC);
    
    
    
    audio = new Audio();

    // carregar músicas e efeitos sonoros
    audio->Add(MUSIC, "Resources/theme2.wav");
    //audio->Add(ENGINE, "Resources/CarEngine.wav");
    //audio->Add(COLLISION, "Resources/Collision.wav");

    // carrega sprites e imagens
    //sky = new Sprite("Resources/Sky.png");
    //track = new Sprite("Resources/Track.png");

    // cria e adiciona jogador na cena
    //Player* player = new Player();
    //scene->Add(player, MOVING);

    // cria e adiciona linhas da pista na cena
    //Stripes* stripes = new Stripes();
    //scene->Add(stripes, STATIC);

    // cria e adiciona carros adversários na cena
    //Cars* cars = new Cars();
    //scene->Add(cars, STATIC);

    // inicia música e motor do carro
    //audio->Volume(ENGINE, 0.25f);
    audio->Play(MUSIC, true);
    //audio->Play(ENGINE, true);
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

    for (auto i = ninjaList.begin(); i != ninjaList.end(); ++i) {
        Ninja* currentNinja = *i;
        if (currentNinja->throwKunai != nullptr) {
            Kunai* kunai = new Kunai(currentNinja->throwKunai->posX - 50.0f, currentNinja->throwKunai->posY, currentNinja->throwKunai->velX);//cena se encarrega de deletar
            scene->Add(kunai, STATIC);
            kunaisList.push_back(kunai);//adiciona apenas para ter controle de quais kunais estão an cena,
            //mas o controle do 'delete' é feito pela cena
            //---------------------------------------------------------
            //talvez melhorar desempenho com if evitando 'new' toda vez
            delete currentNinja->throwKunai;
            currentNinja->throwKunai = nullptr;//limpa buffer de kunai, delete xxxxxxxxx lembrar obsss
        }
    }

    if (timerLandNewNinja.Elapsed(3)) {//3s lança novo ninja em posição aleatória da tela
        Ninja* ninja = new Ninja(rand()%window->Width()+ window->Width());
        scene->Add(ninja, MOVING);
        ninjaList.push_back(ninja);
        timerLandNewNinja.Reset();

    }
    

    /* Percorre para saber quais kunais saíram da tela e precisam ser deletadas */
    stringstream ss;
    ss << "tamanho = " <<kunaisList.size() << std::endl;
    for (auto i = kunaisList.begin(); i != kunaisList.end();) {
        ss << "saiu kunai? " << (*i)->isExit << std::boolalpha << std::endl;
        //OutputDebugString(ss.str().c_str());
        //if (kunai->isExit) 
        //deleta da lista também agora para evitar acesso indevido
        //---------------------------------------------------------------------------
        //OBS: otimizar continuar parando de onde começar em vez de recomeçar do zero
        if ((*i)->isExit) {
            scene->Delete(*i, STATIC);//deleta da cena e da memória
            kunaisList.erase(i);//apaga da lista e invalida os iteradores
            i = kunaisList.begin();//recomeça porque os iterators foram inválidos
        }
        else ++i;
    }

    // habilita/desabilita bounding box
    //if (window->KeyPress('B'))
        //viewBBox = !viewBBox;
}

// ------------------------------------------------------------------------------

void WarriorAdventure::Draw()
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

void WarriorAdventure::Finalize()
{
    /*delete track;
    delete sky;
    delete scene;
    delete audio;*/
    //delete ppBlock;
    ninjaList.clear();//limpa lista de ninjas porque vão ser deletados abaixo
    delete scene;
    //delete ppBlock;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(1000, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Warrior Adventure");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new WarriorAdventure());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

