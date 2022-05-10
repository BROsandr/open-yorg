#pragma once

#include "Interface/Layout.hpp"
class BottomLayout: public Layout{
public:
	BottomLayout();	
	void tick() override;
};