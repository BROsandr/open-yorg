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