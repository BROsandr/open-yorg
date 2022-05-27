#pragma once

#include "Graphical.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class Layout;

class Button: public sf::IntRect, public sf::RectangleShape, public Graphical{
public:
	Button(Layout &layout, std::string button);
	void draw() override ;
	void update();
	sf::Vector2f getCenter()const override;
	std::string getButton();
	bool containsMouse();
	
private:
	Layout &layout;
};