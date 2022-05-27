#include "Input/Input.hpp"
#include "Input/InputStateNormal.hpp"
#include "Game.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Algorithms.hpp"
#include "SFML/Window/Event.hpp"

Input::Input(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_) : state(new InputStateNormal{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}), interface(interface){}

void Input::process(const sf::Event &event){
    if (event.type == sf::Event::Closed)
        Game::window->close();
    if (event.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        sf::View windowSizeView{ visibleArea };
        Game::window->setView(windowSizeView);
        interface.windowSizeView = Game::window->getView();
    }
    if(event.type == sf::Event::MouseMoved)
        processMouseMove();
    if (event.type == sf::Event::EventType::MouseWheelScrolled)
        processMouseWheelScroll(event.mouseWheelScroll);

    if (event.type == sf::Event::EventType::MouseButtonReleased)
        processMouseClick(event.mouseButton);
    if (event.type == sf::Event::EventType::KeyPressed)
        processKeys(event.key.code);
}

void Input::processMouseMove(){
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) 
        processMiddleButtonPressed();
    state->processMouseMove();
}

void Input::processMiddleButtonPressed(){
    if(middleButtonPrevPos != sf::Vector2i{NONE, NONE}){
        sf::Vector2i tempPosition = sf::Mouse::getPosition(*Game::window);
        sf::Vector2i delta = -(tempPosition - middleButtonPrevPos);
        if(delta.x || delta.y){
            moveView(static_cast<sf::Vector2f>(delta) / 80.0f);
            middleButtonPrevPos = tempPosition;
        }
    }
    else
        middleButtonPrevPos = sf::Mouse::getPosition(*Game::window);
}

void Input::moveView(const sf::Vector2f delta){
    sf::View view = Game::window->getView();
    view.move(VIEW_MOVE_SPEED * delta.x, VIEW_MOVE_SPEED * delta.y);
    Game::window->setView(view);
}

void Input::processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton){
    if (mouseButton.button == sf::Mouse::Button::Left)
        processMouseLeftClick({mouseButton.x, mouseButton.y});
    if (mouseButton.button == sf::Mouse::Button::Middle)
        middleButtonPrevPos = { NONE, NONE };
}

void Input::processMouseLeftClick(const sf::Vector2i &clickPosition){
    if(std::string button { interface.getButtonIfClicked() }; button != "")
        processKeys(stringToKey(button));
    sf::Vector2f floatCoord = Game::window->mapPixelToCoords(clickPosition);
    FieldCoord fieldCell = Algorithms::vector2fToFieldCoord(floatCoord);
    if(floatCoord.x < 0 || floatCoord.y < 0){
        fieldCell.x -= floatCoord.x < 0? 1: 0;
        fieldCell.y -= floatCoord.y < 0? 1: 0;
    }
    std::cerr << std::endl << fieldCell.x << ' ' << fieldCell.y << ' ';
    if(Algorithms::inFieldBounds(floatCoord))
        interface.selectCell(fieldCell); 
    else
        std::cerr << "out of field bounds" << std::endl;
}

sf::Keyboard::Key Input::stringToKey(std::string &str){
    if(str == "B")
        return sf::Keyboard::Key::B;
    if(str == "C")
        return sf::Keyboard::Key::C;
    else
        throw "Unknown key";
}

void Input::processKeys(const sf::Keyboard::Key &key){
    switch(key){
    //fall through
    case sf::Keyboard::Key::Left:
    case sf::Keyboard::Key::Right:
    case sf::Keyboard::Key::Down:
    case sf::Keyboard::Key::Up:
        processViewMove(key);
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
    default:
        std::cout << "Unknown key\n";
    }
}
    

void Input::zoomView(const double delta){
    double zoom = 1 - delta * ZOOM_SPEED;
    sf::View view = Game::window->getView();
    view.zoom(zoom);
    Game::window->setView(view);
}