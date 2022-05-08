#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <functional>
#include <utility>

#include "Building/CrystalMine.hpp"
#include "Field/EmptyFieldCell.hpp"
#include "InputStateFutureRoad.hpp"
#include "InputStateNormal.hpp"
#include "Building/Transporter.hpp"
#include "Field/FieldCell.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include "Algorithms.hpp"
#include "Building/Base.hpp"
#include "Resource/Crystal.hpp"
#include "Enemy/CasualEnemy.hpp"
#include "Building/Mine.hpp"
#include "Building/Cannon.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "Resource/Iron.hpp"
#include "Building/IronMine.hpp"
#include "Building/Wall.hpp"
#include "SFML/Window/Mouse.hpp"
#include "ValuesAndTypes.hpp"
#include <thread>

InputStateNormal::InputStateNormal(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_): InputState{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}{};

InputState* InputStateNormal::process(const sf::Event &event){
    if(event.type == sf::Event::EventType::MouseButtonPressed)
        if(event.key.code == sf::Mouse::Middle){
            std::thread t{&InputStateNormal::processMiddleButtonPressed, this};
            t.detach();
        }

    if (event.type == sf::Event::EventType::KeyPressed)
        return processKeys(event.key);

    if (event.type == sf::Event::EventType::MouseButtonReleased)
        processMouseClick(event.mouseButton);
    
    return nullptr;
}

bool InputStateNormal::isValidBuildingPosition(const FieldCoord &position){
    return field.get(position).fieldCellType == FieldCell::FieldCellType::empty;
}

void InputStateNormal::processMouseClick(const sf::Event::MouseButtonEvent  &mouseButton){
    if (mouseButton.button == sf::Mouse::Button::Left)
        processMouseLeftClick({mouseButton.x, mouseButton.y});
}

void InputStateNormal::processMiddleButtonPressed(){
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

InputState* InputStateNormal::place(const sf::Keyboard::Key &key){
    const FieldCoord &position = interface.selectedCell;

    if (!isValidBuildingPosition(position)){
        std::cout << "Invalid building postion" << std::endl;
        return;
    }
    if (interface.selectedCell != NONE_FIELD_CELL){
		FieldCell *fieldCell = nullptr;
        int buildingCost = 0;
        switch(key){
        case sf::Keyboard::R:
            fieldCell = field.set(new Crystal{ interface.selectedCell });
            break;
        case sf::Keyboard::I:
            fieldCell = field.set(new Iron{interface.selectedCell});
            break;
        case sf::Keyboard::E:
            new CasualEnemy{ interface.selectedCell, enemies, pathSearchField, bullets, field, damageCircles};
            break;
        default:
            std::tie(fieldCell, buildingCost) = build(key);
        }
		if(fieldCell){
			return new InputStateFutureRoad{field, interface, pathSearchField, enemies, bullets, damageCircles, resourceBalls, road, buildingCost};
        }
        else 
            return nullptr;
    }
}


std::pair<FieldCell*, int> InputStateNormal::build(const sf::Keyboard::Key &key){
    FieldCell *fieldCell = nullptr;
    switch (key) {
    case sf::Keyboard::B:
        fieldCell = field.set(new Base{ field, interface.selectedCell });
        break;
    case sf::Keyboard::M:
        fieldCell = field.set(new CrystalMine{ field, interface.selectedCell, resourceBalls, road });
        break;
    case sf::Keyboard::C:
        fieldCell = field.set(new Cannon{ interface.selectedCell, enemies, bullets, damageCircles });
        break;
    case sf::Keyboard::T:
        fieldCell = field.set(new Transporter{ interface.selectedCell });
        break;
    case sf::Keyboard::O:
        fieldCell = field.set(new IronMine{ field, interface.selectedCell, resourceBalls, road });
        break;
    case sf::Keyboard::W:
        fieldCell = field.set(new Wall{ interface.selectedCell });
        break;
    }
    if(fieldCell){
        Building &building {static_cast<Building&>(*fieldCell)};
        int buildingCost = building.cost;
            if(canAfford(building))
                return std::make_pair(fieldCell, buildingCost);
            else{
                std::cerr << "Cannot afford" << std::endl;
                field.set(new EmptyFieldCell{fieldCell->getCoord()});
            }
    }
    return std::make_pair(nullptr, 0);
}

bool InputStateNormal::canAfford(Building &building){
    if(building.cost > field.getCrystals())
        return false;
    else
        return true;
}

void InputStateNormal::upgrade(Building &building){
    building.upgrade();
}

void InputStateNormal::moveView(const sf::Vector2f delta){
    sf::View view = Game::window->getView();
    view.move(VIEW_MOVE_SPEED * delta.x, VIEW_MOVE_SPEED * delta.y);
    Game::window->setView(view);
}

InputState* InputStateNormal::processKeys(const sf::Event::KeyEvent &key){
    switch(key.code){
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
    case sf::Keyboard::Key::F1:
        if(FieldCell &fieldCell {field.get( interface.selectedCell)}; fieldCell.fieldCellType == FieldCell::FieldCellType::building)
            upgrade(static_cast<Building&>(fieldCell));
        else
            std::cerr << "Cannot be upgraded" << std::endl;
        break;
    case sf::Keyboard::Key::F9:
        if(field.basePosition != NONE_FIELD_CELL)
            field.incrementCrystals();
        break;
    case sf::Keyboard::Key::B:
    //fall-through
    case sf::Keyboard::Key::R:
    case sf::Keyboard::Key::E:
    case sf::Keyboard::Key::M:
    case sf::Keyboard::Key::C:
    case sf::Keyboard::Key::T:
    case sf::Keyboard::I:
    case sf::Keyboard::O:
    case sf::Keyboard::W:
        return place(key.code);
        break;
    default:
        std::cerr << std::endl << "detected unrecognized Key event" << std::endl;
    }
    
    return nullptr;
}

void InputStateNormal::processMouseLeftClick(const sf::Vector2i &clickPosition){
    sf::Vector2f floatCoord = Game::window->mapPixelToCoords(clickPosition);
    FieldCoord fieldCell = Algorithms::vector2fToFieldCoord(floatCoord);
    std::cerr << std::endl << fieldCell.x << ' ' << fieldCell.y << ' ';

    if( (fieldCell.x < FIELD_LENGTH && floatCoord.x >= 0) && (fieldCell.y < FIELD_WIDTH && floatCoord.y >= 0) )
        interface.selectCell(fieldCell); 
    else
        std::cerr << "out of field bounds" << std::endl;
}