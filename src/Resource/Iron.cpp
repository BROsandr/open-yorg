#include "Resource/Iron.hpp"
#include "Game.hpp"

Iron::Iron(const FieldCoord &fieldCoord): Resource{fieldCoord}{
    text.setString("I");
    resourceType = ResourceType::iron;
}

void Iron::draw() {
    Resource::draw();
    Game::window->draw(*this);
}