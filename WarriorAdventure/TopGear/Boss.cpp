#include "Boss.h"
#include "WarriorAdventure.h"
#include "Wind.h"
#include "Boss_fight.h"
#include "Bola_de_fogo.h"


Boss::Boss()
{
	bossSet = new TileSet("Resources/robo.png", 79, 110, 10, 50);
	bossAni = new Animation(bossSet, 0.08f, true);//0.01f

    uint idle[10] = { 9,8,7,6,5,4,3,2,1,0 };
    uint shoot[24] = { 9,8,7,6,5,4,3,2,1,0,9,8,7,6,5,4,3,2,1,0,19,18,17,16};
    uint explosion[16] = { 29,28,27,26,25,24,23,22,22,22,22,22,22,22,21,20 };
    uint chegando_teletransporte[10] = { 39,38,37,36,35,34,33,32,31,30 };
    uint saindo_teletransporte[10] = { 49,48,47,46,45,44,43,42,41,40 };
   

    bossAni->Add(static_cast<uint>(StateBoss::IDLE), idle, 10);
    bossAni->Add(static_cast<uint>(StateBoss::SHOOT), shoot, 24);
    bossAni->Add(static_cast<uint>(StateBoss::EXPLOSION), explosion, 16);
    bossAni->Add(static_cast<uint>(StateBoss::INPUT_TELEPORTATION), chegando_teletransporte, 10);
    bossAni->Add(static_cast<uint>(StateBoss::EXIT_TELEPORTATION), saindo_teletransporte, 10);
    bossAni->Select(static_cast<uint>(stateBoss));

    BBox(new Rect(
        -1 * float(bossSet->TileWidth()) / 2.0f,
        -1 * float(bossSet->TileHeight()) / 2.0f,
        bossSet->TileWidth() / 2.0f,
        bossSet->TileHeight() / 2.0f)
    );

    MoveTo(900, 410);
    type = BOSS;
    qual_bloco_esta = 2;
    tiros_tomados = 0;
    tiros_necessarios_para_morrer = 1;
    atingivel = true;
    temporizador.Start();
}


Boss::~Boss()
{
    delete bossSet;
    delete bossAni;
    //delete speedFont;
}

void Boss::Update()
{
    
    if (tiros_tomados >= tiros_necessarios_para_morrer)
    {
        
        stateBoss = StateBoss::EXPLOSION;
        bossAni->Select(static_cast<uint>(stateBoss));
        
    }
    
    if (bossAni->Frame() == 20)
    {
        Boss_fight::scene->Delete();
        Boss_fight::chefe_derrotado = true;
        OutputDebugString("Boss derrotado\n");
    }

    if ((bossAni->Frame() >= 47 || bossAni->Frame() <= 32) && ((bossAni->Frame() >= 29 || bossAni->Frame() <= 19)))
    {
        atingivel = true;
    }
    else
    {
        atingivel = false;
    }

    if (bossAni->Frame() == 41)
    {

        if (qual_bloco_esta == 2)
        {
            MoveTo(900, 240);
            qual_bloco_esta = 1;
        }
        else
        {
            if (qual_bloco_esta == 1)
            {
                MoveTo(900, 410);
                qual_bloco_esta = 2;
            }
        }

        stateBoss = StateBoss::INPUT_TELEPORTATION;
        bossAni->Select(static_cast<uint>(stateBoss));

    }

    

    if (bossAni->Frame() == 31)
    {
        stateBoss = StateBoss::SHOOT;
        bossAni->Select(static_cast<uint>(stateBoss));
    }

    if (bossAni->Frame() == 0)
    {
        stateBoss = StateBoss::SHOOT;
        bossAni->Select(static_cast<uint>(stateBoss));
    }

    //atirar
    if (bossAni->Frame() == 16) {


        if (temporizador.Elapsed(1.5))
        {
            throwTiro = new ThrowTiro();//deletado na criação da kunai no warrioradventure
            throwTiro->posX = X();//- float(ninjaSet->TileWidth()) / 2.0f;
            throwTiro->posY = Y();
            //throwTiro->velX = speedX - 200.0f;
            Bola_de_fogo* fireball = new Bola_de_fogo(X() - float(bossSet->TileWidth())/2.0f, Y(), -150.0f);
            Boss_fight::scene->Add(fireball, STATIC);
            Boss_fight::audio->Play(FIREBALLSOUND, false);
            Boss_fight::audio->Volume(FIREBALLSOUND, 50);
            temporizador.Reset();
        }

        
    }



    bossAni->NextFrame();
}


void Boss::Draw()
{
    // desenha carro
    bossAni->Draw(X(), Y(), Layer::FRONT);
}

void Boss::OnCollision(Object* obj)
{

    // não está transparente
    if (atingivel == true)
    {
        if (obj->Type() == WIND)
        {
            ++tiros_tomados;
            stringstream ss;
            ss << "se fu****** " << std::endl;
            OutputDebugString(ss.str().c_str());
            Wind* ventinho = static_cast<Wind*>(obj);
            Boss_fight::scene->Delete(ventinho, MOVING);
        }
    }
    
}

void Boss::teletransporte()
{

    stateBoss = StateBoss::EXIT_TELEPORTATION;
    bossAni->Select(static_cast<uint>(stateBoss));

}