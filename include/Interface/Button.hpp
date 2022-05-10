#pragma once

#include "Graphical.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class Layout;

class Button: public sf::RectangleShape, public Graphical{
public:
	Button(Layout &layout);
	void draw() override ;
	void update();
	sf::Vector2f getCenter()const;
	
private:
	Layout &layout;
};