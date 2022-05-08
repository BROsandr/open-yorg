#pragma once

#include "Field/FieldCell.hpp"
#include "Can/CanHaveHp.hpp"
#include "ValuesAndTypes.hpp"

class Building: public FieldCell, public CanHaveHp{
public:
	ResourceType compatibleResource = ResourceType::none;
	enum class BuildingType{
		mine,

		none 
	} buildingType = BuildingType::none;
	int cost = NONE;

    Building(const FieldCoord &fieldCoord, int connectionRadius, int cost);
	void update() override;
	virtual void upgrade();

};