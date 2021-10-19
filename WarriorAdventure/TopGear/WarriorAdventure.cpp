#include "Engine.h"
#include "WarriorAdventure.h"
#include "Player.h"
#include "block.h"
#include <stdlib.h>
// ------------------------------------------------------------------------------
// inicialização de membros estáticos da classe

Audio* WarriorAdventure::audio = nullptr;
Scene* WarriorAdventure::scene = nullptr;


list<Tiro_aviao*> WarriorAdventure::engineList;
list<Wind*> WarriorAdventure::windList;
list<Block*> WarriorAdventure::blockList;
list<Ninja*> WarriorAdventure::ninjaList;

// ------------------------------------------------------------------------------
float Block::speedX = -100.0f;
void WarriorAdventure::Init()
{
    // cria gerenciadores
    scene = new Scene();
    background = new Background();
    //player = new Player();
    for (uint i = 0; i < quantityNinjas; ++i) {
        Ninja* ninja = new Ninja(i*500.0f + 800.0f);
        scene->Add(ninja, MOVING);
        WarriorAdventure::ninjaList.push_back(ninja);//adiciona ponteiro apenas para saber os ninjas da cena
    }
    //ninja = new Ninja(560);
    //ninja2 = new Ninja(700);
    scene->Add(Fase_mestra::player, MOVING);

    airplane = new Airplane();
    scene->Add(airplane,STATIC);
    loadBlocks(ppBlock);
    scene->Add(background, STATIC);
    //scene->Add(player, MOVING);
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

    if (Fase_mestra::player->died){
        Fase_mestra::player->died = false;
        Fase_mestra::qual_nivel = Fase_mestra::SelectedLevel::LEVEL2;
        Fase_mestra::NextLevel<Boss_fight>();
    }
    else {
        //cria kunais
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
        //cria ninjas
        if (timerLandNewNinja.Elapsed(4)) {//4s lança novo ninja em posição aleatória da tela
           // OutputDebugString("************************* criou ninja\n");
            ++quantityNinjas;
            Ninja* ninja = new Ninja(float(rand() % window->Width() + window->Width()));
            scene->Add(ninja, MOVING);
            ninjaList.push_back(ninja);
            timerLandNewNinja.Reset();
        }
        /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
        /* OBSS: OTIMIZAR O FOR COMPONENTIZANDO EM FUNÇÃO GENÉRICA  */


        /* deleta kunais */
        for (auto i = kunaisList.begin(); i != kunaisList.end();) {
            //OBS: otimizar continuar parando de onde começar em vez de recomeçar do zero
            if ((*i)->isExit) {
                scene->Delete(*i, STATIC);//deleta da cena e da memória
                kunaisList.erase(i);//apaga da lista e invalida os iteradores
                i = kunaisList.begin();//recomeça porque os iterators foram inválidos
            }
            else ++i;
        }
        //-----------------------------------------------
        //fazeeeeeeeeeeeeeeeer
        /* deleta ninjas */

        for (auto i = ninjaList.begin(); i != ninjaList.end();) {
            Ninja* ninja = *i;
            stringstream o;
            if (ninja->Y() - 132.0f / 2.0f >= window->Height()) {
                //OutputDebugString("************************* deletou ninjaaaaaaa\n");
                --quantityNinjas;
                //WarriorAdventure::scene->Delete(ninja, STATIC);
                ninjaList.erase(i);
                i = ninjaList.begin();
            }//30 e altura da catraca
            else {
                ++i;
            }
        }
        //deleta catraca
        for (auto i = engineList.begin(); i != engineList.end();) {
            Tiro_aviao* tiro = *i;
            stringstream o;
            if (tiro->Y() - 30.0f >= window->Height()) {
                WarriorAdventure::scene->Delete(tiro, STATIC);
                engineList.erase(i);
                i = engineList.begin();
            }//30 e altura da catraca
            else {
                tiro->Rotate(-500.0f * gameTime);
                ++i;
            }
        }

        for (auto i = windList.begin(); i != windList.end();) {
            Wind* wind = *i;
            stringstream o;
            if (wind->X() - 35.0f >= window->Width()) {
                OutputDebugString("xxxxxxxxxxxxxxxxxxxxxxx deletooooooou vento");
                OutputDebugString(o.str().c_str());
                WarriorAdventure::scene->Delete(wind, MOVING);
                windList.erase(i);
                i = windList.begin();
            }
            else {
                ++i;
            }
        }

        stringstream x;
        //x << "&&&&&&&&&&&& &&&&& qtd de cblcoooooos "<< blockList.size()<< std::endl;
        //OutputDebugString(x.str().c_str());
        for (auto i = blockList.begin(); i != blockList.end();) {
            Block* block = *i;
            stringstream o;
            if (block->X() + block->width / 2.0f <= 0.0f) {
                OutputDebugString("xxxxxxxxxxxxxxxxxxxxxxx deletooooooou blockooo");
                WarriorAdventure::scene->Delete(block, STATIC);
                blockList.erase(i);
                i = blockList.begin();
            }
            else {
                ++i;
            }
        }

        // habilita/desabilita bounding box
        //if (window->KeyPress('B'))
            //viewBBox = !viewBBox;
        stringstream r;
        r << "fim do update = " << quantityNinjas << std::endl;
        //OutputDebugString(r.str().c_str());
    }

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
    engineList.clear();
    kunaisList.clear();
    blockList.clear();
    windList.clear();
    delete [] ppBlock;
    //Fase_mestra::player->speedX
    scene->Remove(Fase_mestra::player, MOVING);
    delete scene;
    delete audio;
}

void WarriorAdventure::loadBlocks(Block ** ppBlock) {
    /* criação dos blocos pelo .txt block-position */
    std::ifstream fin;
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
        WarriorAdventure::blockList.push_back(ppBlock[i]);
    }

    fin.close();
}


// ----------------------------------------------------------------------------


