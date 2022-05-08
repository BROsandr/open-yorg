#include "Building/Transporter.hpp"
#include "Game.hpp"

Transporter::Transporter(const FieldCoord &fieldCoord): Building{fieldCoord, 3, 0}{
    text.setString("T");
    renderTexture.draw(text);
}

void Transporter::draw(){
    Building::draw();
    renderTexture.display();
    Game::window->draw(*this);
}