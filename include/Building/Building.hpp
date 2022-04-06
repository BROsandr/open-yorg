#pragma once

#include "Field/FieldCell.hpp"
#include "Can/CanHaveHp.hpp"
#include "ValuesAndTypes.hpp"

class Building: public FieldCell, public CanHaveHp{
public:
    Building(const FieldCoord &fieldCoord);
public:
	void update() override;

};