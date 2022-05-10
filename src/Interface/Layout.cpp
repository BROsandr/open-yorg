#include "Interface/Layout.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "Game.hpp"

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

sf::Vector2f Layout::getNextDrawPos(){
    sf::Vector2f drawPos = nextDrawPos;
    nextDrawPos += buttonSize;
    return drawPos;
}

sf::RenderTexture &Layout::getTexture(){
    return renderTexture;
}