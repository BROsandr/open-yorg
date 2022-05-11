#include "Field/Road.hpp"
#include "Building/Building.hpp"
#include "Field/EmptyFieldCell.hpp"
#include "Resource/Resource.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "ValuesAndTypes.hpp"
#include "Field/Field.hpp"
#include "Field/FieldCell.hpp"
#include "Algorithms.hpp"
#include "lemon/adaptors.h"
#include "lemon/core.h"
#include "lemon/list_graph.h"
#include <algorithm>
#include "Game.hpp"
#include "Building/Mine.hpp"

Road::Road(Field &field): Graph{field}{
    nodeField.resize(FIELD_LENGTH);
    for (int col = 0; col < FIELD_LENGTH; col++) {
        nodeField[col].resize(FIELD_WIDTH);
        for (int row = 0; row < FIELD_WIDTH; row++)
            graphField.addNode();
    }
    {
        int i = 0;
        for (lemon::ListDigraph::NodeIt it(graphField); it != lemon::INVALID; ++it, i++) {
            FieldCoord fieldCoord = Algorithms::flatIndexToFieldCoord(i);
            nodeField[fieldCoord.x][fieldCoord.y] = it;
        }
    }
    for (int col = 0; col < FIELD_LENGTH; col++)
        for (int row = 0; row < FIELD_WIDTH; row++){
            nodeFilter[nodeField[col][row]] = false;
            nodeFilterFuture[nodeField[col][row]] = false;
        }

    for (int col = 0; col < FIELD_LENGTH; col++)
        for (int row = 0; row < FIELD_WIDTH; row++)
            coordMap[nodeField[col][row]] = { col, row };
}

void Road::update(){
    for(lemon::FilterNodes<lemon::ListDigraph>::ArcIt arc(futureSubGraphField); arc != lemon::INVALID; ++arc){
        futureSubGraphField.erase(arc);
    }
	for(lemon::FilterNodes<lemon::ListDigraph>::NodeIt node(futureSubGraphField); node != lemon::INVALID; ++node)
        nodeFilterFuture[node] = false;
    for(int col = 0; col < FIELD_LENGTH; col++)
        for(int row = 0; row < FIELD_WIDTH; row++)
			if(lemon::ListDigraph::NodeIt node = nodeField[col][row]; field.get({col, row}).fieldCellType != FieldCell::FieldCellType::empty){
                nodeFilterFuture[node] = true;
                connect(node);
            }
}

bool Road::mineHasResource(const FieldCoord &source, ResourceType type){
    if(!nodeFilter[nodeField[source.x][source.y]])
        return false;
    for(lemon::FilterNodes<lemon::ListDigraph>::ArcIt arc(subGraphField); arc != lemon::INVALID; ++arc){
		if(FieldCell &fieldCell = field.get(coordMap[subGraphField.source(arc)]); fieldCell.fieldCellType == FieldCell::FieldCellType::resource && static_cast<Resource&>(fieldCell).resourceType == type && Algorithms::belongsToCircle(fieldCell.getCoord(), source, 2))
            return true;
    }
    return false;
}

void Road::draw(){
    for(lemon::FilterNodes<lemon::ListDigraph>::ArcIt it(futureSubGraphField); it != lemon::INVALID; ++it)
        drawArc(it);
}

void Road::drawArc(lemon::FilterNodes<lemon::ListDigraph>::ArcIt arcIt) {
    lemon::ListDigraph::Node sourceNode = futureSubGraphField.source(arcIt);
    lemon::ListDigraph::Node targetNode = futureSubGraphField.target(arcIt);
    sf::Vector2f source = Algorithms::fieldCoordToVector2fCentered(coordMap[sourceNode]);
    sf::Vector2f target = Algorithms::fieldCoordToVector2fCentered(coordMap[targetNode]);
    float length = Algorithms::calculateEuclideanDistance(source, target);
    float thickness = 1;
    sf::RectangleShape line;
    line.setSize({length, thickness});
    line.setPosition(source);
    line.setFillColor(isFutureArc(sourceNode, targetNode)? sf::Color::Black: sf::Color::Green);
    line.setRotation(Algorithms::radiansToDegrees( Algorithms::calculateAzimuth(source, target) ));
    Game::window->draw(line);
}

bool Road::isFutureArc(lemon::ListDigraph::Node &source, lemon::ListDigraph::Node &target){
    return nodeFilterFuture[source] != nodeFilter[source] || nodeFilterFuture[target] != nodeFilter[target];
}

void Road::connect(lemon::ListDigraph::NodeIt node){
    FieldCoord nodeCoord = {coordMap[node].x, coordMap[node].y};
    int nodeConnectionRadius = field.get({coordMap[node].x, coordMap[node].y}).connectionRadius;
    for(lemon::FilterNodes<lemon::ListDigraph>::NodeIt it(futureSubGraphField); it != lemon::INVALID; ++it){
        if(node == it)
            continue;
		FieldCoord itCoord = {coordMap[it].x, coordMap[it].y};
        int itConnectionRadius = field.get({coordMap[it].x, coordMap[it].y}).connectionRadius;
        int connectionRadius = std::max(nodeConnectionRadius, itConnectionRadius);
		if(Algorithms::belongsToCircle(itCoord, nodeCoord, connectionRadius) && canConnect(itCoord, nodeCoord)){
            futureSubGraphField.addArc(it, node);
            futureSubGraphField.addArc(node, it);
        }
    }
}

bool Road::canConnect(FieldCoord leftCoord, FieldCoord rightCoord){
    FieldCell &leftFieldCell = field.get(leftCoord);
    FieldCell &rightFieldCell = field.get(rightCoord);
    if(leftFieldCell.fieldCellType == FieldCell::FieldCellType::resource && rightFieldCell.fieldCellType == FieldCell::FieldCellType::resource)
        return false;
    if(leftFieldCell.fieldCellType != FieldCell::FieldCellType::resource && rightFieldCell.fieldCellType != FieldCell::FieldCellType::resource)
        return true;
    if(leftFieldCell.fieldCellType == FieldCell::FieldCellType::resource){
        if(Building &building = static_cast<Building&>( rightFieldCell ); building.buildingType == Building::BuildingType::mine)
            if(Mine &mine = static_cast<Mine&>(building); mine.compatibleResource == static_cast<Resource&>(leftFieldCell).resourceType)
                return true;
            else
                return false;
        else 
            return false;
    }
    if(rightFieldCell.fieldCellType == FieldCell::FieldCellType::resource){
        if(Building &building = static_cast<Building&>( leftFieldCell ); building.buildingType == Building::BuildingType::mine)
            if(Mine &mine = static_cast<Mine&>(building); mine.compatibleResource == static_cast<Resource&>(rightFieldCell).resourceType)
                return true;
            else
                return false;
        else 
            return false;
    }
    return false;
}



std::pair<FieldCoord, bool> Road::generatePath(const FieldCoord &source_, ResourceType type){
    if (source_ == NONE_FIELD_CELL) {
        return std::make_pair(NONE_FIELD_CELL, false);
    }
    lemon::ListDigraph::Node source(nodeField[source_.x][source_.y]);
    if(!nodeFilter[source])
        return std::make_pair(NONE_FIELD_CELL, false);

    lemon::FilterNodes<lemon::ListDigraph>::ArcMap<int> lengthMap(subGraphField);
    for (lemon::ListDigraph::ArcIt it(graphField); it != lemon::INVALID; ++it)
        lengthMap[it] = 1;
    dijkstra_t<lemon::ListDigraph> dijkstra{ subGraphField, lengthMap };
    dijkstra.init();
    dijkstra.addSource(source);
    bool reachedDestination = false;
    while(!reachedDestination){
        lemon::ListDigraph::Node nextNode = dijkstra.nextNode();
        if(nextNode == lemon::INVALID)
            return std::make_pair(NONE_FIELD_CELL, false);
        if(Building &building = static_cast<Building&>(field.get(coordMap[nextNode])); building.compatibleResource == type && building.buildingType != Building::BuildingType::mine)
            reachedDestination = true;
        else
            dijkstra.processNextNode();
    }

    lemon::ListDigraph::Node destination = dijkstra.nextNode();
    FieldCoord destinationCoord = field.get(coordMap[destination]).getCoord();

    dijkstra_t<lemon::ListDigraph>::Path path{ dijkstra.path(destination) };
    {
        int pathLength = path.length();
		if(pathLength <= 1){
            return std::make_pair(destinationCoord, dijkstra.reached(destination));
        }
        int pathLengthIndex = pathLength - 1;
        dijkstra_t<lemon::ListDigraph>::Path::RevArcIt it(path);

        for (; pathLengthIndex > 1; ++it, pathLengthIndex--);
        FieldCoord fieldCoord = getCoord(it);
        return std::make_pair(fieldCoord, true);
    }
}

void Road::showFutureRoad(){
    // std::cout << "printing future\n";
    // for (lemon::FilterNodes<lemon::ListDigraph>::ArcIt it(subGraphField); it != lemon::INVALID; ++it)
    //     std::cout << coordMap[subGraphField.source(it)].x << ' '<< coordMap[subGraphField.source(it)].y << std::endl;
    // std::cout << "ending printing future\n";
}

void Road::showRealRoad(bool revert){
    for(lemon::FilterNodes<lemon::ListDigraph>::NodeIt node(futureSubGraphField); node != lemon::INVALID; ++node)
        if(revert){
            if( nodeFilter[node] != nodeFilterFuture[node])
                field.set(new EmptyFieldCell(coordMap[node]));
        }
        else
            nodeFilter[node] = nodeFilterFuture[node];

    // subGraphField = futureSubGraphField;
    // for(lemon::FilterNodes<lemon::ListDigraph>::ArcIt arc(futureSubGraphField); arc != lemon::INVALID; ++arc)
    //     subGraphField.addArc(futureSubGraphField.source(arc), futureSubGraphField.target(arc));
    // lemon::copy
}

bool Road::isFutureCell(FieldCoord &fieldCoord){
    lemon::ListDigraph::Node &node = nodeField[fieldCoord.x][fieldCoord.y];
    return nodeFilterFuture[node] != nodeFilter[node];
}