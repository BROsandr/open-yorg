#pragma once

#include <list>
#include "Interface/Layout.hpp"

class Layouts{
public:
	Layouts();
	void update();
	void draw();
	
private:
	std::list<Layout*> layouts;
};