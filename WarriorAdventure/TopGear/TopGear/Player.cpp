#include "Player.h" 
#include "WarriorAdventure.h" 
// ---------------------------------------------------------------------------------
Player::Player() {
    // carrega folhas de sprites do carro
    playerSet = new TileSet("Resources/warrior.png", 91, 109, 10, 40);
    playerAni = new Animation(playerSet, 0.05f, true);//0.01f

    uint jump[10] = { 0, 1, 2, 3, 4 };
    uint fall[10] = { 5, 6, 7, 8, 9};
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

    // configura posição do objeto
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
    stringstream ssx;
  
    if (window->KeyDown(VK_RIGHT)) Translate(speedX * gameTime,0.0f);//deve ser 0 e não mudar no y
    if (window->KeyDown(VK_LEFT)) Translate(-1.0f * speedX * gameTime, 0.0f);//deve ser 0 e não mudar no y
   
   stringstream c;
   c << "on = " << onBlock << std::endl;
       
    /* pulo */
    if (window->KeyPress(VK_SPACE) && statePlayer == StatePlayer::RUN) {// 
        //releaseTimerJump = false;
        //timerJump.Start();
        statePlayer = StatePlayer::JUMP;
        playerAni->Restart();
        playerAni->Select(static_cast<uint>(statePlayer));
        speedY = -500.0f;
        //timerJump.Start();
    }
    c << "speeeeedy " << speedY << std::endl;
    //OutputDebugString(c.str().c_str());
    stringstream ss;
    
    //primeira execução do pulo o onBlock ainda é true, garante primeiro deslocamento com velocidade Y definida no pulo
    //--------------------------------------------------------------------
    //não estando no bloco a gravidade age
    if(!onBlock) speedY += gravity;//gravidade age quando não está no bloco. Evitar excesso de soma e overfllow futuro
    Translate(0.0f, speedY * gameTime);
    onBlock = false;///precisa colidir para reativar
    //speedY == 0 no pulo quando atingiu o ápice da parábola e speedY > 0 quando está caindo
    //ss << "yyyyyyyyyyyyyyyy " << speedY << std::endl;

    //----------------------------
    //corrige para queda
    if (speedY >= 0 && statePlayer == StatePlayer::JUMP) {
        //ss << "set fall " << speedY << std::endl;
        //OutputDebugString(ss.str().c_str());
        statePlayer = StatePlayer::FALL;//está caindo já que velocidade positiva
        playerAni->Restart();
        playerAni->Select(static_cast<uint>(statePlayer));
    }
    //OBS: cuidado no igual a zero porque no pico da parábola e no chão ambos a valocidade vale zero
    //sempre andando no y 
  

    /*
    if (window->KeyPress(VK_SPACE)) {
        if (releaseTimerJump) {
            timerJump.Start();
            releaseTimerJump = false;
        }
    }

    if (releaseTimerJump == false) {
        playerAni->Select(JUMP);
        Translate(0.0f, speedY * gameTime);
        if (timerJump.Elapsed() < 0.6f) {
            speedY = -200.0f;
        }
        else if(timerJump.Elapsed() < 1.2f) {
            speedY = 200.0f;
        }
        else {
            timerJump.Stop();
            timerJump.Reset();
            releaseTimerJump = true;
            playerAni->Select(RUN);
        }
    }
    */
    /* ataque */
    if (window->KeyPress(VK_LBUTTON) && statePlayer == StatePlayer::RUN) {
        statePlayer = StatePlayer::ATTACK;
        playerAni->Restart();
        playerAni->Select(static_cast<uint>(statePlayer));
    }
    if (statePlayer == StatePlayer::ATTACK) {
        stringstream s;
        s << "xxxxxxxxxxxxxxxxxxx atacooooou" << playerAni->Frame() << std::endl;
        
        if (playerAni->Frame() == 29) {
            statePlayer = StatePlayer::RUN;
            playerAni->Restart();
            playerAni->Select(static_cast<uint>(statePlayer));
        }
        /* criar vento */
        if (playerAni->Frame() == 25 && throwWind) {
            throwWind = false;
            s << "criou vento" << std::endl;
            Wind* wind = new Wind(X() + float(playerSet->TileWidth()) / 2.0f, Y());
            WarriorAdventure::scene->Add(wind, MOVING);
            WarriorAdventure::windList.push_back(wind);
        }
        if(playerAni->Frame() != 25) throwWind = true;//não para botar no mesmo if porque iria ficar trocando permite, nega, permite, nega no mesmo frame
        OutputDebugString(s.str().c_str());
    }


    //if (window->KeyDown(VK_DOWN))
        //speed -= 1000 * gameTime;

    // limita velocidade máxima e mínima
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

    // se mantém sempre dentro da pista
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
    
    // animação dos pneus deve se ajustar com a velocidade
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
    playerAni->Draw(x, y, Layer::FRONT, 1.0f, rotation);

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
            //ss << "===================== diferença " << Y() + playerSet->TileHeight() / 2.0f - (block->Y() - 40.0f) << std::endl;
            //OutputDebugString(ss.str().c_str());
            //+ 0.5 apenas por imprecisão do ponto flutuante. 
            //Trabalhar com comparação pura é trabalhar no limite em que qualquer "trepidação" pode influênciar negativamente
            if (Y() + float(playerSet->TileHeight())/2.0f - (block->Y() - 40.0f) <= speedY * gameTime /*dist. máx permitida de percorrer */ + 5.0f) {//intervalo de confiança, depende da velocidade que está caindo.
                //quanto mais alto a queda, maior deve ser o intervalo porque velocidade maior entreria mais no bloco
                //intervalo de aceitação.
                //speedY * gameTime é o quanto o player percorreria se estivesse na superfície exata e estando a essa velocidade de queda.
                //OBS: o == 0 do <= garante que quando velY == 0 o player não caia. A imprecisão intrínseca de ponto flutuante causa isso.
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
    //if (obj->Type() == KUNAI) {
       // stringstream ss;
        //ss << "tipoooooo " << obj->Type() << std::endl;
        //OutputDebugString(ss.str().c_str());
        //speedX = Block::speedX;
        //died = true;
       // statePlayer = StatePlayer::IDLE;
       // playerAni->Select(static_cast<uint>(statePlayer));
   // }
    // desenha velocidade
    /*text.str("");
    text.width(3);
    text.fill('0');
    text << int(speed / 10.0f);
    speedFont->Draw(790, 222, "888", Color(0.1f, 0.1f, 0.1f, 1.0f));
    speedFont->Draw(790, 222, text.str(), Color(1.0f, 0.0f, 0.0f, 1.0f));*/
}

// -------------------------------------------------------------------------------