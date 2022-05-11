#include <time.h>

#include "Building/Building.hpp"
#include "Can/CanStore.hpp"
#include "Field/Field.hpp"
#include "Field/EmptyFieldCell.hpp"
#include "Field/FieldCell.hpp"
#include "ValuesAndTypes.hpp"

Field::Field() : road(*this), pathSearchField{*this} {
    srand(time(0));

    field.resize(FIELD_LENGTH);

    for(auto col = field.begin(); col < field.end(); col++){
        col->resize(FIELD_WIDTH);
        for(auto row = col->begin(); row < col->end(); row++){
            *row = new EmptyFieldCell({ int(col - field.begin()), int(row - col->begin()) });
            // cellType = rand();
            // if(cellType != FieldCellType::none)
            //     placeNew(FieldCell(row, column), toResource(cellType))
            // else{
            //     placeNew(FieldCell(row, column), None())
            // }
        }
    }
}

void Field::tick(){
    update();
    pathSearchField.update();
    road.update();
    draw();
    road.draw();
}

void Field::update(){
    for (auto &row : field)
        for (auto &col : row) {
            if (col->deleted) {
                FieldCoord fieldCoord = col->getCoord();
                set(new EmptyFieldCell{ fieldCoord });
            }
            else
                col->update();
        }
}

void Field::draw(){
    for(auto &row: field)
        for(auto &col: row)
            col->draw();
}

FieldCell* Field::set(FieldCell *const fieldCell){
    const FieldCoord &fieldCoord = fieldCell->getCoord();
    delete field[fieldCoord.x][fieldCoord.y];
    field[fieldCoord.x][fieldCoord.y] = fieldCell;
    return fieldCell;
    // field[fieldCoord.x][fieldCoord.y].setCoord(fieldCoord)
    // switch(fieldCell.type){
    // case FieldCellType::building:
    //     buildingType = static_cast<Building>(fieldCell) . type
    //     switch(buildingType){
    //     case BuildingType::base:
    //         basePosition = fieldCoord
    //         break;
    //     }
    //     break;
    // }
    // pathSearchField.placeNew(fieldCoord, fieldCell)
    // road.placeNew(fieldCoord)
}

FieldCell& Field::get(const FieldCoord &fieldCoord){
    return *field[fieldCoord.x][fieldCoord.y];
}

Field::~Field(){
    for(auto &row: field)
        for(auto &col: row)
            delete col;
}

bool Field::isFutureCell(FieldCoord &fieldCoord){
    return road.isFutureCell(fieldCoord);
}

int Field::getCrystals(){
    if(basePosition != NONE_FIELD_CELL)
        return static_cast<CanStore&>( get(basePosition) ).storage;
    else
        return 0;
}
void Field::incrementCrystals(){
    static_cast<CanStore&>( get(basePosition) ).storage++;
}

void Field::decreaseCrystals(int amount){
    static_cast<CanStore&>( get(basePosition) ).storage -= amount;
}

FieldCell& Field::relocate(FieldCell &fieldCell, const FieldCoord newCoord){
    if(FieldCell &fieldCellInNewCoord = get(newCoord); fieldCellInNewCoord.fieldCellType == FieldCell::FieldCellType::empty){
        FieldCoord oldCoord = fieldCell.getCoord();
        fieldCell.setCoord(newCoord);
        fieldCellInNewCoord.setCoord(oldCoord);
        field[oldCoord.x][oldCoord.y] = &fieldCellInNewCoord;
        field[newCoord.x][newCoord.y] = &fieldCell;
    }
    return fieldCell;
}