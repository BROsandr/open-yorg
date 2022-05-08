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
        windowSizeView.zoom(zoomFactor);
        Game::window->setView(windowSizeView);
    }
    if (event.type == sf::Event::EventType::MouseWheelScrolled)
        processMouseWheelScroll(event.mouseWheelScroll);
	if(InputState *state_ = state->process(event); state_){
        delete state;
        state = state_;
    }
}

void Input::processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll){
    zoomView(mouseWheelScroll.delta);
}

void Input::zoomView(const double delta){
    zoomFactor = 1 - delta * ZOOM_SPEED;
    sf::View view = Game::window->getView();
    view.zoom(zoomFactor);
    Game::window->setView(view);
}