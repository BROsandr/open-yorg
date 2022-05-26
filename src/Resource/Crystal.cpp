#include "Resource/Crystal.hpp"
#include "Game.hpp"

Crystal::Crystal(const FieldCoord &fieldCoord): Resource{fieldCoord}{
    text.setString("CR");
    resourceType = ResourceType::crystal;
}

void Crystal::draw() {
    Resource::draw();
    Game::window->draw(*this);
}