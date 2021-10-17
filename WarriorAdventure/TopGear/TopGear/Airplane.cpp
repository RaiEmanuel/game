#include "Airplane.h" 
#include "WarriorAdventure.h" 

// ---------------------------------------------------------------------------------

static int contador_saida_da_tela;
static int tiros_lancados;

Airplane::Airplane() {

    // carrega folhas de sprites do carro
    airplaneSet = new TileSet("Resources/airplane.png", 153, 132, 5, 10);
    airplaneAni = new Animation(airplaneSet, 0.50f, true);//0.01f

    

    contador_saida_da_tela = 0;
    tiros_lancados = 0;

    


    uint seq_aviao[7] = { 4,3,9,8,7,6,5 };
    
    #define SEQUENCIA_AVIAO 666

    airplaneAni->Add(SEQUENCIA_AVIAO,seq_aviao, 7);
    

    airplaneAni->Select(SEQUENCIA_AVIAO);

    // cria bounding box
    BBox(new Rect(
        -1 * float(airplaneSet->TileWidth()) / 2.0f,
        -1 * float(airplaneSet->TileHeight()) / 2.0f,
        airplaneSet->TileWidth() / 2.0f,
        airplaneSet->TileHeight() / 2.0f)
    );

    // configura posi��o do objeto
    MoveTo((float)window->Width()+airplaneSet->TileWidth()/2,window->CenterY()-200.0f);
    type = AIRPLANE;

}

// ---------------------------------------------------------------------------------

Airplane::~Airplane()
{
    //delete carAni;
    //delete carSet;
    //delete speedFont;
}

// ---------------------------------------------------------------------------------

void Airplane::Update()
{
    {
        
        Translate(-200.0f * gameTime, 0.0f * gameTime);
       
        
        if (X() < 0.0f-airplaneSet->TileWidth())
        {
            MoveTo((float)window->Width() + airplaneSet->TileWidth()+800 / 2, window->CenterY() -200.0f);
            contador_saida_da_tela++;
        }
       
    }

	// inicia o tiro num frame aleatorio
    if (airplaneAni->Frame() == 5)
    {
        airplaneAni->NextFrame();
        
		
		// s� atira no m�ximo uma vez por passada na tela e se estiver numa faixa que n�o deixe uma parte da sprite da bala para fora da tela
        if (tiros_lancados <= contador_saida_da_tela && X() < 950 && X() > 50 )
        {
            Tiro_aviao * tiro = new Tiro_aviao(X(), Y());
            WarriorAdventure::scene->Add(tiro, STATIC);
            WarriorAdventure::engineList.push_back(tiro);
            tiros_lancados++;

            //stringstream ss;
            //ss << "Desenhou tiro do aviao = (" << X() << ", " << Y() << ")" << std::endl;

            //OutputDebugString(ss.str().c_str());

        }
       
       
       
    }


    if (airplaneAni->Frame() == 7)
    {
        airplaneAni->Select(SEQUENCIA_AVIAO);
    }

    airplaneAni->NextFrame();
}

// -------------------------------------------------------------------------------

void Airplane::Draw()
{
    // desenha carro
    airplaneAni->Draw(X(), Y(), Layer::FRONT);
    //stringstream ss;
    //ss << "Desenhou aviao na posicao = (" << X() << ", " << Y() << ")" << std::endl;
    //OutputDebugString(ss.str().c_str());
}

void Airplane::OnCollision(Object* obj)
{
    

       
}

// -------------------------------------------------------------------------------