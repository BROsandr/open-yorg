#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <list>
#include "Interface/Layout.hpp"
#include <string>

class Layouts{
public:
	Layouts();
	void update();
	void draw();
	std::string getButtonIfClicked();
	
private:
	std::list<Layout*> layouts;
};