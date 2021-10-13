/**********************************************************************************
// TopGear (C�digo Fonte)
//
// Cria��o:     11 Jul 2019
// Atualiza��o: 06 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Uso da escala em um jogo estilo TopGear
//
**********************************************************************************/

#include "Engine.h"
#include "WarriorAdventure.h"
//#include "Stripes.h"
#include "Player.h"
#include "block.h"
//#include "Cars.h"

// ------------------------------------------------------------------------------
// inicializa��o de membros est�ticos da classe

//Audio* TopGear::audio = nullptr;
//float   TopGear::speed = 1000.0f;

// ------------------------------------------------------------------------------

void WarriorAdventure::Init()
{
    // cria gerenciadores
    scene = new Scene();
    background = new Background();
    player = new Player();
    /* cria��o dos blocos pelo .txt block-position */
    fin.open("Resources/block-position.txt", std::ios_base::in);
    if (!fin.is_open()) {
        //return EXIT_FAILURE;
        //erro na leitura
    }
    int numBlocks; //n�mero de blocos a serem lidos
    float posX; //posi��o x do bloco
    char typeBlock = 'M';//tipo do bloco
    stringstream ss;
    fin >> numBlocks;
    ss << "xxxxxxxxxxxxxxx lidos y blocos = " << numBlocks<<std::endl;
    OutputDebugString(ss.str().c_str());
    ppBlock = new Block *[numBlocks];
    for (int i = 0; i < numBlocks; ++i) {
        fin >> posX >> typeBlock;
        //enum TypeBlock { UNIQUE, TWO, SMALL, MEDIUM, LARGE };
        switch (typeBlock) {
        case 'U':
            ppBlock[i] = new Block(UNIQUE, posX);
            break;
        case 'T':
            ppBlock[i] = new Block(TWO, posX);
            break;
        case 'S':
            ppBlock[i] = new Block(SMALL, posX);
            break;
        case 'M':
            ppBlock[i] = new Block(MEDIUM, posX);
            break;
        case 'L':
            ppBlock[i] = new Block(LARGE, posX);
            break;
        }
        scene->Add(ppBlock[i], STATIC);//objeto deletado pela cena, apenos o ppBlock deletar manualmente
    }

    fin.close();
    //adi��o na cena
    scene->Add(background, STATIC);
    scene->Add(player, MOVING);
    
    
    
    //audio = new Audio();

    // carregar m�sicas e efeitos sonoros
    //audio->Add(MUSIC, "Resources/Soundtrack.wav");
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

    // cria e adiciona carros advers�rios na cena
    //Cars* cars = new Cars();
    //scene->Add(cars, STATIC);

    // inicia m�sica e motor do carro
    //audio->Volume(ENGINE, 0.25f);
    //audio->Play(MUSIC, true);
    //audio->Play(ENGINE, true);
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
        //scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void WarriorAdventure::Finalize()
{
    /*delete track;
    delete sky;
    delete scene;
    delete audio;*/
    //delete ppBlock;
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
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new WarriorAdventure());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

