#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <functional>
#include <utility>

#include "Building/CrystalMine.hpp"
#include "Field/EmptyFieldCell.hpp"
#include "Input/InputStateFutureRoad.hpp"
#include "Input/InputStateNormal.hpp"
#include "Building/Transporter.hpp"
#include "Field/FieldCell.hpp"
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
#include "ValuesAndTypes.hpp"

InputStateNormal::InputStateNormal(Field &field, Interface &interface, PathSearchField &pathSearchField, Enemies &enemies, Bullets &bullets, DamageCircles &damageCircles_, ResourceBalls &resourceBalls_, Road &road_): InputState{field, interface, pathSearchField, enemies, bullets, damageCircles_, resourceBalls_, road_}{};

bool InputStateNormal::isValidBuildingPosition(const FieldCoord &position){
    return field.get(position).fieldCellType == FieldCell::FieldCellType::empty;
}



InputState* InputStateNormal::place(const sf::Keyboard::Key &key){
    const FieldCoord &position = interface.selectedCell;

    if (!isValidBuildingPosition(position)){
        std::cout << "Invalid building postion" << std::endl;
        return nullptr;
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
			return new InputStateFutureRoad{field, interface, pathSearchField, enemies, bullets, damageCircles, resourceBalls, road, buildingCost, fieldCell};
        }
    }
    return nullptr;
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
    default:
        std::cout << "Unknown key\n";
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

InputState* InputStateNormal::processKeys(const sf::Keyboard::Key &key){
    switch(key){
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
        return place(key);
        break;
    default:
        std::cerr << std::endl << "detected unrecognized Key event" << std::endl;
    }
    
    return nullptr;
}
void InputStateNormal::processMouseMove(){
}