#include "Building/Transporter.hpp"
#include "Game.hpp"

Transporter::Transporter(const FieldCoord &fieldCoord): Building{fieldCoord, 3, 0}{
    text.setString("T");
}

void Transporter::draw(){
    Building::draw();
    Game::window->draw(*this);
}