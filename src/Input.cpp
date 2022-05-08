#include "Input.hpp"
#include "InputStateNormal.hpp"
#include "Game.hpp"

Input::Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_) : interface(interface), state(new InputStateNormal{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}){}

void Input::process(const sf::Event &event){
    if (event.type == sf::Event::Closed)
        Game::window->close();
    if (event.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        sf::View windowSizeView{ visibleArea };
        interface.windowSizeView = windowSizeView;
        Game::window->setView(windowSizeView);
    }
	if(InputState *state_ = state->process(event); state_){
        delete state;
        state = state_;
    }
}
