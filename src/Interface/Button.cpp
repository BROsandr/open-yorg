#include "Interface/Button.hpp"
#include "Graphical.hpp"
#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>

Button::Button(Layout &layout, std::string button): layout(layout){
    setPosition(layout.getNextDrawPos());
    setSize({layout.buttonSize.x, layout.buttonSize.y});
    left = layout.getSelfPosition().x + getPosition().x;
    top = layout.getSelfPosition().y + getPosition().y;
    width = getSize().x;
    height = getSize().y;
    setOutlineColor(UNSELECTED);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);

    setTexture(&renderTexture.getTexture());
    text.setString(button);
}

std::string Button::getButton(){
    return text.getString();
}

void Button::draw(){
    Graphical::draw();
    layout.getTexture().draw(*this);
}

void Button::update(){
}

sf::Vector2f Button::getCenter()const{
    return getPosition() + sf::Vector2f{ getSize().x / 2, getSize().y / 2 };
}

bool Button::containsMouse(){
    return contains(sf::Mouse::getPosition(*Game::window));
}