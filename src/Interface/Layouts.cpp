#include "Interface/Layouts.hpp"
#include "Interface/Button.hpp"
#include "Interface/BottomLayout.hpp"

Layouts::Layouts(){
	layouts.emplace_back(new BottomLayout{});
}
void Layouts::update(){
	for (auto &layout: layouts) {
		layout->tick();
	}
}
void Layouts::draw(){
}

std::string Layouts::getButtonIfClicked(){
	for(auto &el: layouts)
		if(std::string button { el->getButtonIfClicked() }; button != "")
			return button;
	return "";
}