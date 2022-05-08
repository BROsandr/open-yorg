#include "Input/Input.hpp"
#include "Input/InputStateNormal.hpp"
#include "Game.hpp"
#include <thread>
#include "Algorithms.hpp"

Input::Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_) : interface(interface), state(new InputStateNormal{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}){}

void Input::process(const sf::Event &event){
    if (event.type == sf::Event::Closed)
        Game::window->close();
    if(event.type == sf::Event::EventType::MouseButtonPressed)
        if(event.key.code == sf::Mouse::Middle){
            std::thread t{&Input::processMiddleButtonPressed, this};
            t.detach();
        }
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

    if (event.type == sf::Event::EventType::MouseButtonReleased)
        processMouseClick(event.mouseButton);
    if (event.type == sf::Event::EventType::KeyPressed)
        processKeys(event.key);
}

void Input::processMiddleButtonPressed(){
    middleButtonPrevPos = sf::Vector2i{NONE, NONE};
    while(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        if(middleButtonPrevPos != sf::Vector2i{NONE, NONE}){
            sf::Vector2i tempPosition = sf::Mouse::getPosition();
            sf::Vector2i delta = tempPosition - middleButtonPrevPos;
            if(delta.x || delta.y){
                moveView(static_cast<sf::Vector2f>(delta) / 50.0f);
                middleButtonPrevPos = tempPosition;
            }
        }
        else
            middleButtonPrevPos = sf::Mouse::getPosition();
}

void Input::moveView(const sf::Vector2f delta){
    sf::View view = Game::window->getView();
    view.move(VIEW_MOVE_SPEED * delta.x, VIEW_MOVE_SPEED * delta.y);
    Game::window->setView(view);
}

void Input::processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton){
    if (mouseButton.button == sf::Mouse::Button::Left)
        processMouseLeftClick({mouseButton.x, mouseButton.y});
}

void Input::processMouseLeftClick(const sf::Vector2i &clickPosition){
    sf::Vector2f floatCoord = Game::window->mapPixelToCoords(clickPosition);
    FieldCoord fieldCell = Algorithms::vector2fToFieldCoord(floatCoord);
    std::cerr << std::endl << fieldCell.x << ' ' << fieldCell.y << ' ';

    if( (fieldCell.x < FIELD_LENGTH && floatCoord.x >= 0) && (fieldCell.y < FIELD_WIDTH && floatCoord.y >= 0) )
        interface.selectCell(fieldCell); 
    else
        std::cerr << "out of field bounds" << std::endl;
}

void Input::processKeys(const sf::Event::KeyEvent &key){
    switch(key.code){
    //fall through
    case sf::Keyboard::Key::Left:
    case sf::Keyboard::Key::Right:
    case sf::Keyboard::Key::Down:
    case sf::Keyboard::Key::Up:
        processViewMove(key.code);
        break;
    default:
        if(InputState *state_ = state->processKeys(key); state_){
            delete state;
            state = state_;
        }
    }
}

void Input::processMouseWheelScroll(const sf::Event::MouseWheelScrollEvent &mouseWheelScroll){
    zoomView(mouseWheelScroll.delta);
}

void Input::processViewMove(const sf::Keyboard::Key &key){
    switch(key){
    case sf::Keyboard::Key::Left:
        moveView(left);
        break;
    case sf::Keyboard::Key::Right:
        moveView(right);
        break;
    case sf::Keyboard::Key::Down:
        moveView(down);
        break;
    case sf::Keyboard::Key::Up:
        moveView(up);
        break;
    }
}
    

void Input::zoomView(const double delta){
    zoomFactor = 1 - delta * ZOOM_SPEED;
    sf::View view = Game::window->getView();
    view.zoom(zoomFactor);
    Game::window->setView(view);
}