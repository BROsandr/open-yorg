#pragma once

#include "SFML/Graphics/Color.hpp"
#include "ValuesAndTypes.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>

class Graphical{
public:
    bool deleted = false;

    Graphical();
    virtual sf::Vector2f getCenter() const = 0;
    virtual void draw();
    virtual ~Graphical() = default;

protected:
    sf::Texture backgroundTexture;
    sf::Text text;
    sf::RenderTexture renderTexture;
    
    virtual void setColor(sf::Color color = BACKGROUND);
};