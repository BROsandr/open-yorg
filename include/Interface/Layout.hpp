#pragma once

#include <list>
#include "Interface/Button.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"

class Layout{
public:
	const sf::Vector2f buttonSize{CELL_LENGTH, CELL_WIDTH};
	virtual void tick();
	Layout();
	sf::Vector2f getNextDrawPos();
	sf::RenderTexture &getTexture();
	
protected:
	std::list<Button> buttons;
	sf::RenderTexture renderTexture;
private:
	sf::Vector2f nextDrawPos{ NULL, NULL};
};