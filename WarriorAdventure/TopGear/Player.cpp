#include "Player.h" 
#include "WarriorAdventure.h" 
#include "Boss_fight.h"
#include "Fase_mestra.h"
// ---------------------------------------------------------------------------------
Player::Player() {
    // carrega folhas de sprites do carro
    playerSet = new TileSet("Resources/warrior.png", 91, 109, 10, 40);
    playerAni = new Animation(playerSet, 0.05f, true);//0.01f

    uint jump[5] = { 0, 1, 2, 3, 4 };
    uint fall[5] = { 5, 6, 7, 8, 9};
    uint idle[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    uint attack[10] = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };
    uint run[10] = { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39 };

    playerAni->Add(static_cast<int>(StatePlayer::JUMP), jump, 5);
    playerAni->Add(static_cast<int>(StatePlayer::FALL), fall, 5);
    playerAni->Add(static_cast<int>(StatePlayer::IDLE), idle, 10);
    playerAni->Add(static_cast<int>(StatePlayer::ATTACK), attack, 10);
    playerAni->Add(static_cast<int>(StatePlayer::RUN), run, 10);
    playerAni->Select(static_cast<int>(StatePlayer::FALL));

    // cria bounding box
    BBox(new Rect(
        -1*float(playerSet->TileWidth()) / 2.0f,
        -1*float(playerSet->TileHeight()) / 2.0f,
        playerSet->TileWidth() / 2.0f,
        playerSet->TileHeight() / 2.0f)
    );

    // configura posi��o do objeto
    MoveTo(window->CenterX(), window->CenterY());
    type = PLAYER;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete playerAni;
    delete playerSet;
    //delete speedFont;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    stringstream m;
    m << "vxxxxxxxxxxxxxxxxxxxxxxx " << speedX << std::endl;
    OutputDebugString(m.str().c_str());
    if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')){
        statePlayer = StatePlayer::RUN;
        playerAni->Select(static_cast<uint>(statePlayer));
        //playerAni->Restart();
        Translate(speedX * gameTime, 0.0f);//deve ser 0 e n�o mudar no y
    }
    else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
        statePlayer = StatePlayer::RUN;
        playerAni->Select(static_cast<uint>(statePlayer));
        //playerAni->Restart();
        Translate(-1.0f * speedX * gameTime, 0.0f);//deve ser 0 e n�o mudar no y
    }else {
       //if()
        //statePlayer = StatePlayer::IDLE;
        //playerAni->Select(static_cast<uint>(statePlayer));
        //playerAni->Restart();
        Translate(Block::speedX * gameTime, 0.0f);//deve ser 0 e n�o mudar no y 
    }
    /* pulo */
    if ((window->KeyPress(VK_SPACE) || window->KeyPress('W')) /* && statePlayer == StatePlayer::RUN*/ && onBlock) {// 
        statePlayer = StatePlayer::JUMP;
        playerAni->Select(static_cast<uint>(statePlayer));
        playerAni->Restart();
        speedY = -500.0f;
    }
    
    //primeira execu��o do pulo o onBlock ainda � true, garante primeiro deslocamento com velocidade Y definida no pulo
    //--------------------------------------------------------------------
    //n�o estando no bloco a gravidade age
    if(!onBlock) speedY += gravity;//gravidade age quando n�o est� no bloco. Evitar excesso de soma e overfllow futuro
    Translate(0.0f, speedY * gameTime);
    onBlock = false;///precisa colidir para reativar
    

    //----------------------------
    //corrige para anima��o de queda
    if (speedY >= 0 && statePlayer == StatePlayer::JUMP) {
        //ss << "set fall " << speedY << std::endl;
        //OutputDebugString(ss.str().c_str());
        statePlayer = StatePlayer::FALL;//est� caindo j� que velocidade positiva
        playerAni->Restart();
        playerAni->Select(static_cast<uint>(statePlayer));
    }
    //OBS: cuidado no igual a zero porque no pico da par�bola e no ch�o ambos a valocidade vale zero
    //sempre andando no y 
  
    /* ataque */
    if (window->KeyPress(VK_LBUTTON) /* && statePlayer == StatePlayer::RUN*/) {
        statePlayer = StatePlayer::ATTACK;
        playerAni->Restart();
        playerAni->Select(static_cast<uint>(statePlayer));
    }
    if (statePlayer == StatePlayer::ATTACK) {
        stringstream s;
        s << "frameeeeeeeeeee xxxxxxxxxxxxxxxxxxx atacooooou" << playerAni->Frame() << std::endl;
        OutputDebugString(s.str().c_str());
        /* Acabou anima��o e volta a correr */
        if (playerAni->Frame() == 29) {
            statePlayer = StatePlayer::RUN;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        /* frame para criar vento */
        if (playerAni->Frame() == 25 && throwWind) {
            throwWind = false;
            s << "criou vento" << std::endl;
            OutputDebugString(s.str().c_str());
            Wind* wind = new Wind(X() + float(playerSet->TileWidth()) / 2.0f, Y());

            //adicionar na lista da fase 1
            switch (Fase_mestra::qual_nivel)
            {
            case Fase_mestra::SelectedLevel::LEVEL1:
                OutputDebugString("elvelvelvel 111111");
                WarriorAdventure::scene->Add(wind, MOVING);
                WarriorAdventure::windList.push_back(wind);
                break;
            case Fase_mestra::SelectedLevel::LEVEL2:
                //adicionar na lista da fase 2
                OutputDebugString("elvelvelvel 2");
                if (Fase_mestra::qual_nivel == Fase_mestra::SelectedLevel::LEVEL2)
                {
                    Boss_fight::scene->Add(wind, MOVING);
                    Boss_fight::windList2.push_back(wind);
                }
                break;
            }
        }
        //passou da cria��o do vento pode recriar
        if(playerAni->Frame() != 25) throwWind = true;//n�o para botar no mesmo if porque iria ficar trocando permite, nega, permite, nega no mesmo frame
        
    }


    //if (window->KeyDown(VK_DOWN))
        //speed -= 1000 * gameTime;

    // limita velocidade m�xima e m�nima
    /*if (speed > 3000)
        speed = 3000;
    else 
        if (speed < 0) 
            speed = 0;*/

    // usa a velocidade para ajustar o som do motor
    //TopGear::audio->Frequency(ENGINE, 0.5f + speed / 2000.0f);

    // deslocamento leva em conta a velocidade
    //float deltaX = 600 * (pow(speed,0.5f) / 60.0f) * gameTime;

    // giro do volante do carro
    /*if (window->KeyDown(VK_LEFT))
    {
        Translate(-deltaX, 0);
        if (speed > 0)
            carAni->Select(LEFT);
    }
    if (window->KeyDown(VK_RIGHT))
    {
        Translate(deltaX, 0);
        if (speed > 0)
            carAni->Select(RIGHT);
    }
    if ((window->KeyUp(VK_LEFT) && window->KeyUp(VK_RIGHT)) || 
        (window->KeyDown(VK_LEFT) && window->KeyDown(VK_RIGHT)))
    {
        carAni->Select(STRAIGHT);
    }*/

    // se mant�m sempre dentro da pista
    /*if (x < 180)
    {
        carAni->Select(STRAIGHT);
        MoveTo(180.0f, y);
    }
    else if (x > 780)
    {
        carAni->Select(STRAIGHT);
        MoveTo(780.0f, y);
    }
    
    // anima��o dos pneus deve se ajustar com a velocidade
    if (speed > 0)
    {
        carAni->Delay(50.0f/speed);
        carAni->NextFrame();
    }*/
    playerAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Player::Draw()
{
    // desenha carro
    playerAni->Draw(x, y, Layer::FRONT, scale, rotation);

    // desenha velocidade
    /*text.str("");
    text.width(3);
    text.fill('0');
    text << int(speed / 10.0f);
    speedFont->Draw(790, 222, "888", Color(0.1f, 0.1f, 0.1f, 1.0f));
    speedFont->Draw(790, 222, text.str(), Color(1.0f, 0.0f, 0.0f, 1.0f));*/
}

void Player::OnCollision(Object * obj)
{
    // desenha carro
    //playerAni->Draw(x, y, Layer::FRONT);
    if (obj->Type() == BLOCK) {
        Block* block = (Block*)obj;
        onBlock = true;
        stringstream ss;
        ss <<"xxxxxxxxxxxxxxxxx" << static_cast<uint>(statePlayer) << std::endl;
        //1 - run
        //3 - jump
        // 0     1     2      3     4
        //IDLE, RUN, ATTACK, JUMP, FALL
        if (statePlayer != StatePlayer::JUMP) {
            //OutputDebugString(ss.str().c_str());
            //ss << "=================== colidindoooooo "<< Y() + float(playerSet->TileHeight()) / 2.0f - (block->Y() - 40.0f)<<", "<< speedY * gameTime << std::endl;
            //OutputDebugString(ss.str().c_str());
            //ss << "===================== diferen�a " << Y() + playerSet->TileHeight() / 2.0f - (block->Y() - 40.0f) << std::endl;
            //OutputDebugString(ss.str().c_str());
            //+ 0.5 apenas por imprecis�o do ponto flutuante. 
            //Trabalhar com compara��o pura � trabalhar no limite em que qualquer "trepida��o" pode influ�nciar negativamente
            if (Y() + float(playerSet->TileHeight())/2.0f - (block->Y() - 40.0f) <= speedY * gameTime /*dist. m�x permitida de percorrer */ + 5.0f) {//intervalo de confian�a, depende da velocidade que est� caindo.
                //quanto mais alto a queda, maior deve ser o intervalo porque velocidade maior entreria mais no bloco
                //intervalo de aceita��o.
                //speedY * gameTime � o quanto o player percorreria se estivesse na superf�cie exata e estando a essa velocidade de queda.
                //OBS: o == 0 do <= garante que quando velY == 0 o player n�o caia. A imprecis�o intr�nseca de ponto flutuante causa isso.
                speedY = 0.0f;
                onBlock = true;
                //timerJump.Reset();
                //statePlayer = StatePlayer::RUN;
                if (statePlayer == StatePlayer::FALL) {
                    statePlayer = StatePlayer::RUN;
                    playerAni->Restart();
                    playerAni->Select(static_cast<uint>(statePlayer));
                }
                MoveTo(X(), block->Y() - 40.0f - float(playerSet->TileHeight()) / 2.0f);
            }else {
                onBlock = false;
            }
        }
    }
    if (obj->Type() == KUNAI || obj->Type() == TIRO_AVIAO) {
        //speedX = Block::speedX;
        died = true;
       // statePlayer = StatePlayer::IDLE;
        //playerAni->Select(static_cast<uint>(statePlayer));
        //playerAni->Restart();
    }
    // desenha velocidade
    /*text.str("");
    text.width(3);
    text.fill('0');
    text << int(speed / 10.0f);
    speedFont->Draw(790, 222, "888", Color(0.1f, 0.1f, 0.1f, 1.0f));
    speedFont->Draw(790, 222, text.str(), Color(1.0f, 0.0f, 0.0f, 1.0f));*/
}

// -------------------------------------------------------------------------------