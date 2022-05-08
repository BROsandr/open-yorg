#include <assert.h>

#include <SFML/Graphics/Text.hpp>

#include "Building/Base.hpp"
#include "Can/CanStore.hpp"
#include "Game.hpp"
#include "ValuesAndTypes.hpp"

Base::Base(Field &field, const FieldCoord &fieldCoord): field(field), CanStore{fieldCoord, 3, 0}{
    compatibleResource = ResourceType::crystal;
    text.setString("B");
    renderTexture.draw(text);
    if(field.basePosition != NONE_FIELD_CELL){
        printf("\nbasePos = %d %d\n", field.basePosition.x, field.basePosition.y);
        assert(0 && "Base has yet been built");
    }
}

void Base::draw(){
    renderTexture.display();
    Game::window->draw(*this);
    CanStore::draw();
}

void Base::update(){
    CanStore::update();
    field.basePosition = coord;
}

Base::~Base(){
    field.basePosition = NONE_FIELD_CELL;
}