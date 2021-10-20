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

    // configura posição do objeto
    MoveTo(window->CenterX(), window->CenterY());
    type = PLAYER;

    /* inicializa de acordo com fase */
    switch (Fase_mestra::qual_nivel)
    {
    case Fase_mestra::SelectedLevel::MENU:
        statePlayer = StatePlayer::IDLE;
        break;
    case Fase_mestra::SelectedLevel::LEVEL1:
        statePlayer = StatePlayer::FALL;
        break;
    case Fase_mestra::SelectedLevel::LEVEL2:
        statePlayer = StatePlayer::FALL;
        break;
    case Fase_mestra::SelectedLevel::GAMEOVER:
        break;
    case Fase_mestra::SelectedLevel::WIN:
        break;
    }
    playerAni->Select(static_cast<uint>(statePlayer));
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete playerAni;
    delete playerSet;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    stringstream rx;
    stringstream m;
    switch (Fase_mestra::qual_nivel)
    {
    case Fase_mestra::SelectedLevel::MENU:
        if (!Menu::initializedPlayer) {
            OutputDebugString("inicializou playeeeeeeeer\n");
            Menu::initializedPlayer = true;
            statePlayer = StatePlayer::IDLE;
            playerAni->Select(static_cast<uint>(statePlayer));
            MoveTo(window->CenterX(), 300);
        }
        playerAni->NextFrame();
       
        if (window->KeyPress(VK_UP) || window->KeyPress('W')) {
            Fase_mestra::player->Translate(0.0f, -80.0f);
            --Menu::fase_selecionada;
        }else if (window->KeyPress(VK_DOWN) || window->KeyPress('S')) {
            Fase_mestra::player->Translate(0.0f, 80.0f);
            ++Menu::fase_selecionada;
        }
        /* Ajuste de posição */
        if (Fase_mestra::player->Y() < 300.0f) {
            Fase_mestra::player->MoveTo(Fase_mestra::player->X(), 540.0f);
            Menu::fase_selecionada = 3;
        }
        if (Fase_mestra::player->Y() > 540.0f) {
            Fase_mestra::player->MoveTo(Fase_mestra::player->X(), 300.0f);
            Menu::fase_selecionada = 0;
        }
        //lança vento
        if (window->KeyPress(VK_LBUTTON) && throwWind) {
            throwWind = false;
            Menu::escolha_feita = true;
            statePlayer = StatePlayer::ATTACK;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        if (Fase_mestra::player->statePlayer == StatePlayer::ATTACK) {
            if (playerAni->Frame() == 29) {
                throwWind = true; 
                statePlayer = StatePlayer::IDLE;
                playerAni->Select(static_cast<uint>(statePlayer));
                playerAni->Restart();
                Wind* wind = new Wind(Fase_mestra::player->X(), Fase_mestra::player->Y());
                Menu::ventinho = wind;
                Menu::scene->Add(wind, MOVING);
            }
        }
    break;
    /* ***********************  LEVEL 1  ******************** */
    case Fase_mestra::SelectedLevel::LEVEL1:
        if (!WarriorAdventure::initializedPlayer) {
            Fase_mestra::player->points = 0;
            OutputDebugString("inicializou playeeeeeeeer levellll 111111\n");
            WarriorAdventure::initializedPlayer = true;
            statePlayer = StatePlayer::FALL;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
            MoveTo(200, 100);
            Block::speedX = -100.0f;
        }
        playerAni->NextFrame();

        if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
            statePlayer = StatePlayer::RUN;
            playerAni->Select(static_cast<uint>(statePlayer));
            //playerAni->Restart();
            Translate(speedX * gameTime, 0.0f);//deve ser 0 e não mudar no y
        }
        else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
            statePlayer = StatePlayer::RUN;
            playerAni->Select(static_cast<uint>(statePlayer));
            //playerAni->Restart();
            Translate(-1.0f * speedX * gameTime, 0.0f);//deve ser 0 e não mudar no y
        }
      
        /* pulo */
        if ((window->KeyPress(VK_SPACE) || window->KeyPress('W')) /* && statePlayer == StatePlayer::RUN*/ && onBlock) {// 
            statePlayer = StatePlayer::JUMP;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
            speedY = -500.0f;
        }
        /*queda */
        if (Y() >= 700) died = true;
       
        rx << "x =============== " << X() << std::endl;
        OutputDebugString(rx.str().c_str());
        if (X() >= 1700) {
            win = true;
        }

       
        //--------------------------------------------------------------------
        //não estando no bloco a gravidade age
        if (!onBlock) speedY += gravity;//gravidade age quando não está no bloco. Evitar excesso de soma e overfllow futuro
        Translate(0.0f, speedY * gameTime);
        onBlock = false;///precisa colidir para reativar
        //----------------------------
        //corrige para animação de queda
        if (speedY >= 0 && statePlayer == StatePlayer::JUMP) {
            //ss << "set fall " << speedY << std::endl;
            //OutputDebugString(ss.str().c_str());
            statePlayer = StatePlayer::FALL;//está caindo já que velocidade positiva
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        //OBS: cuidado no igual a zero porque no pico da parábola e no chão ambos a valocidade vale zero
        //sempre andando no y 
        /* ataque */
        if (window->KeyPress(VK_LBUTTON)  && statePlayer != StatePlayer::ATTACK) {
            statePlayer = StatePlayer::ATTACK;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        if (statePlayer == StatePlayer::ATTACK) {
            stringstream s;
            /* Acabou animação e volta a correr */
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
                WarriorAdventure::scene->Add(wind, MOVING);
            }
            //passou da criação do vento pode recriar
            if (playerAni->Frame() != 25) throwWind = true;//não para botar no mesmo if porque iria ficar trocando permite, nega, permite, nega no mesmo frame
        }
        break;
    case Fase_mestra::SelectedLevel::LEVEL2:
        if (!Boss_fight::initializedPlayer) {
            OutputDebugString("inicializou playeeeeeeeer levellll 22222\n");
            Boss_fight::initializedPlayer = true;
            statePlayer = StatePlayer::IDLE;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
            //MoveTo(200, 300);
            Block::speedX = 0.0f;
           
        }
        playerAni->NextFrame();
        //ajusta idle. Se for corrida será selecionado abaixo
        if (statePlayer == StatePlayer::RUN) {
            statePlayer = StatePlayer::IDLE;
            playerAni->Select(static_cast<uint>(statePlayer));
        }
        if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
            

            if (statePlayer != StatePlayer::ATTACK)
            {
                statePlayer = StatePlayer::RUN;
                playerAni->Select(static_cast<uint>(statePlayer));
            }

            //playerAni->Restart();
            Translate(speedX * gameTime, 0.0f);//deve ser 0 e não mudar no y
        }
        else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
            if (statePlayer != StatePlayer::ATTACK)
            {
                statePlayer = StatePlayer::RUN;
                playerAni->Select(static_cast<uint>(statePlayer));
            }
            //playerAni->Restart();
            Translate(-1.0f * speedX * gameTime, 0.0f);//deve ser 0 e não mudar no y
        }
        /* pulo */
        if ((window->KeyPress(VK_SPACE) || window->KeyPress('W')) /* && statePlayer == StatePlayer::RUN*/ && onBlock) {// 
            statePlayer = StatePlayer::JUMP;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
            speedY = -500.0f;
        }
        //--------------------------------------------------------------------
        //não estando no bloco a gravidade age
        if (!onBlock) speedY += gravity;//gravidade age quando não está no bloco. Evitar excesso de soma e overfllow futuro
        Translate(0.0f, speedY * gameTime);
        onBlock = false;///precisa colidir para reativar
        //----------------------------
        //corrige para animação de queda
        if (speedY >= 0 && statePlayer == StatePlayer::JUMP) {
            //ss << "set fall " << speedY << std::endl;
            //OutputDebugString(ss.str().c_str());
            statePlayer = StatePlayer::FALL;//está caindo já que velocidade positiva
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        /*queda */
        if (Y() >= 700)
        {
            died = true;
            throwWind = true;
        }
        //OBS: cuidado no igual a zero porque no pico da parábola e no chão ambos a valocidade vale zero
        //sempre andando no y 
        /* ataque */
        if (window->KeyPress(VK_LBUTTON) && statePlayer != StatePlayer::ATTACK) {
            statePlayer = StatePlayer::ATTACK;
            playerAni->Select(static_cast<uint>(statePlayer));
            playerAni->Restart();
        }
        if (statePlayer == StatePlayer::ATTACK) {
            stringstream s;
            /* Acabou animação e volta a correr */

            if (playerAni->Frame() == 29) {
                statePlayer = StatePlayer::IDLE;
                playerAni->Select(static_cast<uint>(statePlayer));
                playerAni->Restart();
                throwWind = true;
            }
            /* frame para criar vento */
            if (/*playerAni->Frame() == 25 &&*/ throwWind) {
                throwWind = false;
                //s << "criou vento" << std::endl;
                //OutputDebugString(s.str().c_str());
                Wind* wind = new Wind(X() + float(playerSet->TileWidth()) / 2.0f, Y());
                Boss_fight::scene->Add(wind, MOVING);
                //Boss_fight::windList2.push_back(wind);
            }
            //passou da criação do vento pode recriar
            //if (playerAni->Frame() != 25) throwWind = true;//não para botar no mesmo if porque iria ficar trocando permite, nega, permite, nega no mesmo frame
        }
        break;
    case Fase_mestra::SelectedLevel::GAMEOVER:
        break;
    case Fase_mestra::SelectedLevel::WIN:
        break;
    }
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
    if (obj->Type() == KUNAI || obj->Type() == TIRO_AVIAO || obj->Type() == FIREBALL || obj->Type() == NINJA) {
        died = true;
    }

    if (obj->Type() == PHONE) {
        Fase_mestra::player->win = true;
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