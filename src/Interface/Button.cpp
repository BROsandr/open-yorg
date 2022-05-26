#include "Interface/Button.hpp"
#include "Graphical.hpp"
#include "Game.hpp"

Button::Button(Layout &layout): layout(layout){
    text.setString("B");
    renderTexture.draw(text);
    setPosition(layout.getNextDrawPos());
    setSize({CELL_LENGTH, CELL_WIDTH});
    setOutlineColor(UNSELECTED);
    setOutlineThickness(CELL_OUTLINE_THICKNESS);

    setTexture(&renderTexture.getTexture());
}

void Button::draw(){
    Graphical::draw();
    renderTexture.display();
    layout.getTexture().draw(*this);
}

void Button::update(){
}

sf::Vector2f Button::getCenter()const{
    return getPosition() + sf::Vector2f{ getSize().x / 2, getSize().y / 2 };
}