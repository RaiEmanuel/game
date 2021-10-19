#include "Ninja.h" 
#include "WarriorAdventure.h" 

// ---------------------------------------------------------------------------------

Ninja::Ninja(float posX) {

    // carrega folhas de sprites do carro
    ninjaSet = new TileSet("Resources/ninja.png", 110, 132, 10, 70);
    ninjaAni = new Animation(ninjaSet, 0.05f, true);//0.01f

    uint idle[10] = { 39,38,37,36,35,34,33,32,31,30 };
    uint run[10] = {  19,18,17,16,15,14,13,12,11,10 };
    uint attack[10] = { 9,8,7,6,5,4,3,2,1,0 };
    uint jump[5] = { 29,28,27,26,25 };
    uint fall[5] = { 24,23,22,21,20 };
    uint land[10] = { 49,48,47,46,45,44,43,42,41,40};
    uint climb[10] = { 59,58,57,56,55,54,53,52,51,50};
    uint jumpattack[5] = { 69,68,67,66,65 };
    uint fallattack[4] = { 64, 63, 62, 61 };
    
    ninjaAni->Add(static_cast<uint>(StateNinja::IDLE), idle, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::RUN), run, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::ATTACK), attack, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::JUMP), jump, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::FALL), fall, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::LAND), land, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::CLIMB), climb, 10);
    ninjaAni->Add(static_cast<uint>(StateNinja::JUMPATTACK), jumpattack, 5);
    ninjaAni->Add(static_cast<uint>(StateNinja::FALLATTACK), fallattack, 4);
   
    ninjaAni->Select(static_cast<uint>(stateNinja));

    // cria bounding box
    BBox(new Rect(
        -1 * float(ninjaSet->TileWidth()) / 2.0f,
        -1 * float(ninjaSet->TileHeight()) / 2.0f,
        ninjaSet->TileWidth() / 2.0f,
        ninjaSet->TileHeight() / 2.0f)
    );

    // configura posição do objeto
    MoveTo(posX, window->CenterY() - window->Height());
    type = NINJA;

}

// ---------------------------------------------------------------------------------

Ninja::~Ninja()
{
    delete ninjaSet;
    delete ninjaAni;
    //delete speedFont;
}

// ---------------------------------------------------------------------------------

void Ninja::Update()
{
    // acelera ou freia
    //NinjaAni->Select(stateNinja);
    //speedX -= 100 * gameTime;
    
    //primeira execução do pulo o onBlock ainda é true, garante primeiro deslocamento com velocidade Y definida no pulo
    if (!onBlock) speedY += gravity;//gravidade age quando não está no bloco. Evitar excesso de soma e overfllow futuro
    Translate(speedX * gameTime, speedY * gameTime);
    onBlock = false;///precisa colidir para reativar
    //speedY == 0 no pulo quando atingiu o ápice da parábola e speedY > 0 quando está caindo
    if (speedY >= 0 && (stateNinja == StateNinja::JUMP || stateNinja == StateNinja::JUMPATTACK)) stateNinja = StateNinja::LAND;//está caindo já que velocidade positiva
    //OBS: cuidado no igual a zero porque no pico da parábola e no chão ambos a valocidade vale zero
    //sempre andando no y 
    if (stateNinja == StateNinja::ATTACK){ //&& window->KeyPress(VK_RETURN)) {
        stringstream ss;
        

       if (ninjaAni->Frame() == 7) {
            //OutputDebugString("Throw");
           ss << "ccccccccccccccccccccriou throwKunai " << std::endl;
           OutputDebugString(ss.str().c_str());
            throwKunai = new ThrowKunai();//deletado na criação da kunai no warrioradventure
            throwKunai->posX = X();//- float(ninjaSet->TileWidth()) / 2.0f;
            throwKunai->posY = Y();
            throwKunai->velX = speedX - 200.0f;
       }
       if (ninjaAni->Frame() == 0) {
           stateNinja = StateNinja::RUN;
           ninjaAni->Select(static_cast<uint>(stateNinja));
       }
    }
    
    ninjaAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Ninja::Draw()
{
    // desenha carro
    ninjaAni->Draw(X(), Y(), Layer::FRONT);
}

void Ninja::OnCollision(Object* obj)
{
    stringstream x;
    if (obj->Type() == BLOCK) {
        Block* block = (Block*)obj;
        onBlock = true;
        stringstream ss;
        /* Colidiu tem que ajustar para ficar certo no bloco */
        /* Não sendo categoria pulo todas animações precisam de ajuste*/
        /* Caso contrário o personagem ficaria fixo */
        /* --------------------------------------------------------------- */
        if (stateNinja != StateNinja::JUMP) {
            //ss << "=================== colidindoooooo "<< Y() + float(playerSet->TileHeight()) / 2.0f - (block->Y() - 40.0f)<<", "<< speedY * gameTime << std::endl;
            //OutputDebugString(ss.str().c_str());
            //ss << "===================== diferença " << Y() + playerSet->TileHeight() / 2.0f - (block->Y() - 40.0f) << std::endl;
            //OutputDebugString(ss.str().c_str());
            //+ 0.5 apenas por imprecisão do ponto flutuante. 
            //Trabalhar com comparação pura é trabalhar no limite em que qualquer "trepidação" pode influênciar negativamente
            if (Y() + float(ninjaSet->TileHeight()) / 2.0f - (block->Y() - 40.0f) <= speedY * gameTime /*dist. máx permitida de percorrer */ + 0.5f) {//intervalo de confiança, depende da velocidade que está caindo.
                //quanto mais alto a queda, maior deve ser o intervalo porque velocidade maior entreria mais no bloco
                //intervalo de aceitação.
                //speedY * gameTime é o quanto o player percorreria se estivesse na superfície exata e estando a essa velocidade de queda.
                //OBS: o == 0 do <= garante que quando velY == 0 o player não caia. A imprecisão intrínseca de ponto flutuante causa isso.
                speedY = 0;
                //timerJump.Reset();
                //statePlayer = StatePlayer::RUN;
                //só muda se for colidindo na queda
                if (stateNinja == StateNinja::FALL || stateNinja == StateNinja::LAND || stateNinja == StateNinja::FALLATTACK) {
                    //ajusta no pós queda
                    stateNinja = StateNinja::ATTACK;
                    ninjaAni->Restart();
                    ninjaAni->Select(static_cast<uint>(stateNinja));
                }
                MoveTo(X(), block->Y() - 40.0f - float(ninjaSet->TileHeight()) / 2.0f);
                onBlock = true;
            }
            else {
                onBlock = false;
            }
            stringstream g;
            //g << std::boolalpha << "status no bloco === " << onBlock << ",,,, " << speedX <<std::endl;
            //OutputDebugString(g.str().c_str());
            //não está no bloco e não está caindo em ocsião normal, então precisa voltar pro bloco
            if (!onBlock && stateNinja != StateNinja::FALL && stateNinja != StateNinja::FALLATTACK && stateNinja != StateNinja::LAND) {
                speedX *= -1;
                Translate(speedX * gameTime, 0.0f);//-1.0f * speedX * gameTime, mas certeza ser 0
            }
        }

    }
}

// -------------------------------------------------------------------------------