#include "Resource/Crystal.hpp"
#include "Game.hpp"

Crystal::Crystal(const FieldCoord &fieldCoord): Resource{fieldCoord}{
    text.setString("R");
    renderTexture.draw(text);
    resourceType = ResourceType::crystal;
}

void Crystal::draw() {
    Resource::draw();
    renderTexture.display();
    Game::window->draw(*this);
}