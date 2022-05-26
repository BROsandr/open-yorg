#include <assert.h>

#include <SFML/Graphics/Text.hpp>

#include "Building/Base.hpp"
#include "Can/CanStore.hpp"
#include "Game.hpp"
#include "ValuesAndTypes.hpp"

Base::Base(Field &field, const FieldCoord &fieldCoord): CanStore{fieldCoord, 3, 0}, field(field){
    compatibleResource = ResourceType::crystal;
    text.setString("B");
    if(field.basePosition != NONE_FIELD_CELL){
        printf("\nbasePos = %d %d\n", field.basePosition.x, field.basePosition.y);
        assert(0 && "Base has yet been built");
    }
}

void Base::draw(){
    CanStore::draw();
    Game::window->draw(*this);
}

void Base::update(){
    CanStore::update();
    field.basePosition = coord;
}

Base::~Base(){
    field.basePosition = NONE_FIELD_CELL;
}