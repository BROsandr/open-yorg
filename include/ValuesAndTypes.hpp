#pragma once

#include <SFML/System/Vector2.hpp>
#include <lemon/list_graph.h>
#include <lemon/dijkstra.h>
#include <lemon/adaptors.h>

using FieldCoord = sf::Vector2i;
using Azimuth = double;

template<class GR>
using dijkstra_t = lemon::Dijkstra<lemon::FilterNodes<GR>, typename GR::template ArcMap<int> >;
enum class ResourceType{
	crystal,
	iron,
	none,

	n
};

#define NONE -1
#define NONE_FIELD_CELL FieldCoord(-1, -1) 
#define NONE_VECTOR2F sf::Vector2f(-1, -1)

#define SELECTED sf::Color::Blue
#define UNSELECTED sf::Color::Black
#define BACKGROUND sf::Color::Cyan

#define ZOOM_SPEED 0.1
#define SPEED 1
#define VIEW_MOVE_SPEED 20

#define FIELD_LENGTH 20
#define FIELD_WIDTH 20

#define CELL_LENGTH 20
#define CELL_WIDTH 20
#define CELL_OUTLINE_THICKNESS -1

#define DAY_DURATION NONE
#define NIGHT_DURATION NONE

#define DAMAGE_CIRCLE_LIFE_TIME 0.3