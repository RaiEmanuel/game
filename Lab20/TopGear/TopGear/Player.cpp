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
    

    playerAni->Add(JUMP, jump, 5);
    playerAni->Add(FALL, fall, 5);
    playerAni->Add(IDLE, idle, 10);
    playerAni->Add(ATTACK, attack, 10);
    playerAni->Add(RUN, run, 10);
    playerAni->Select(statePlayer);

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
    //delete carAni;
    //delete carSet;
    //delete speedFont;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // acelera ou freia
    //playerAni->Select(statePlayer);
    if (window->KeyDown(VK_RIGHT))
        Translate(speedX * gameTime, 0.0f);
    if (window->KeyDown(VK_LEFT))
        Translate(-speedX * gameTime, 0.0f);
    /* pulo */
    if (window->KeyPress(VK_SPACE) && onBlock) {
        //speedY = -100.0f;
        //releaseTimerJump = false;
        //timerJump.Start();
        statePlayer = JUMP;
        playerAni->Select(statePlayer);
        timerJump.Start();
    }
    stringstream ss;
    float gravity = 30.0f;
    if (statePlayer == JUMP){
        if (timerJump.Elapsed() <= 0.2f) {
            speedY -= gravity;
        }
        else {
            timerJump.Stop();
            //timerJump.Reset();
            statePlayer = FALL;
            playerAni->Select(statePlayer);
        }
    }
    if (!onBlock && statePlayer != JUMP) {
        speedY += gravity;
    }
    
    Translate(0.0f, speedY * gameTime);
    onBlock = false;///precisa colidir para reativar
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
    if (window->KeyPress(VK_LBUTTON) && statePlayer != ATTACK) {
        statePlayer = ATTACK;
        playerAni->Restart();
        playerAni->Select(statePlayer);
    }
    if (statePlayer == ATTACK) {
        stringstream s;
        s << "xxxxxxxxxxxxxxxxxxx atacooooou" << playerAni->Frame() << std::endl;
        OutputDebugString(s.str().c_str());
        if (playerAni->Frame() == 29) {
            statePlayer = RUN;
            playerAni->Select(statePlayer);
            playerAni->Restart();
        }
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
    playerAni->Draw(x, y, Layer::FRONT);

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
                  
            stringstream ss;
        if (statePlayer != JUMP) {
            //ss << "===================== diferença " << Y() + playerSet->TileHeight() / 2.0f - (block->Y() - 40.0f) << std::endl;
            //OutputDebugString(ss.str().c_str());
            if (Y() + playerSet->TileHeight()/2.0f - (block->Y() - 40.0f) <= gravity) {
                //intervalo de aceitação
                speedY = 0;
                timerJump.Reset();
                statePlayer = RUN;
                playerAni->Select(statePlayer);
                MoveTo(X(), block->Y() - 40.0f - playerSet->TileHeight() / 2.0f);
                onBlock = true;
            }
            else {
                onBlock = false;
            }
        }
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