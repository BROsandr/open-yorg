#pragma once

#include "Interface/Layout.hpp"
#include "ValuesAndTypes.hpp"
#include <SFML/System/Vector2.hpp>
class BottomLayout: public Layout{
public:
	BottomLayout();	
	void tick() override;
	sf::Vector2f getNextDrawPos() override;
private:
	sf::Vector2f nextDrawPos{ 5, 5};
};