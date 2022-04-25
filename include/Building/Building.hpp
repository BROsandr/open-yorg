#pragma once

#include "Field/FieldCell.hpp"
#include "Can/CanHaveHp.hpp"
#include "ValuesAndTypes.hpp"

class Building: public FieldCell, public CanHaveHp{
public:
	ResourceType compatibleResource = ResourceType::none;
    Building(const FieldCoord &fieldCoord, int connectionRadius);
public:
	void update() override;

};