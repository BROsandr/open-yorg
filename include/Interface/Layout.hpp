#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "Interface/Button.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"

class Layout{
public:
	const sf::Vector2f buttonSize{70, 70};
	virtual void tick();
	Layout();
	virtual sf::Vector2f getNextDrawPos() = 0;
	sf::RenderTexture &getTexture();
	std::string getButtonIfClicked();
	sf::Vector2f getSelfPosition();
	
protected:
	sf::Vector2f position = NONE_VECTOR2F;
	std::list<Button> buttons;
	sf::RenderTexture renderTexture;
};