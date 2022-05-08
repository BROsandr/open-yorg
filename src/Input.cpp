#include "Input.hpp"
#include "InputStateNormal.hpp"
#include "Game.hpp"

Input::Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_) : state(new InputStateNormal{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}){}

void Input::process(const sf::Event &event){
    if (event.type == sf::Event::Closed)
        Game::window->close();
	if(InputState *state_ = state->process(event); state_){
        delete state;
        state = state_;
    }
}
