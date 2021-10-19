#include "ButtonMenu.h"
#include "TopGear.h"
#include <sstream>
using std::stringstream;

// ---------------------------------------------------------------------------------

ButtonMenu::ButtonMenu(string button, float posX, float posY)
{
    spriteButton = new Sprite("Resources/"+button);
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

ButtonMenu::~ButtonMenu()
{
    delete spriteButton;
}

// ---------------------------------------------------------------------------------

void ButtonMenu::Update()
{
  
}

// -------------------------------------------------------------------------------

void ButtonMenu::Draw()
{
    spriteButton->Draw(X(), Y(), Layer::FRONT);
}

// -------------------------------------------------------------------------------


void ButtonMenu::OnCollision(Object * obj)
{

}