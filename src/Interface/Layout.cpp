#include "Interface/Layout.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>

Layout::Layout(){
}

void Layout::tick(){
    for (auto &el : buttons) {
        el.update();
        el.draw();
    }
    buttons.remove_if([](const Button &button){
        return button.deleted;
    });
    renderTexture.display();
}

sf::RenderTexture &Layout::getTexture(){
    return renderTexture;
}

std::string Layout::getButtonIfClicked(){
    for(auto &el:buttons)
        if(el.containsMouse())
            return el.getButton();
    return "";
}

sf::Vector2f Layout::getSelfPosition(){
    return position;
}