#include "Field/PathSearchField.hpp"
#include "Algorithms.hpp"
#include "Field/Field.hpp"
#include "Field/FieldCell.hpp"
#include "lemon/list_graph.h"

PathSearchField::PathSearchField(Field &field) : Graph{ field } {
    nodeField.resize(FIELD_LENGTH);
    for (int col = 0; col < FIELD_LENGTH; col++) {
        nodeField[col].resize(FIELD_WIDTH);
        for (int row = 0; row < FIELD_WIDTH; row++)
            graphField.addNode();
    }
    {
        int i = 0;
        for (lemon::ListGraph::NodeIt it(graphField); it != lemon::INVALID; ++it, i++) {
            FieldCoord fieldCoord = Algorithms::flatIndexToFieldCoord(i);
            nodeField[fieldCoord.x][fieldCoord.y] = it;
        }
    }
    for (int col = 0; col < FIELD_LENGTH; col++)
        for (int row = 0; row < FIELD_WIDTH; row++)
            nodeFilter[nodeField[col][row]] = true;
    for (int col = 0; col < FIELD_LENGTH - 1; col++) {
        for (int row = 0; row < FIELD_WIDTH - 1; row++) {
            graphField.addEdge(nodeField[col][row + 1], nodeField[col][row]);
            graphField.addEdge(nodeField[col + 1][row], nodeField[col][row]);
        }
    }

    for (int col = 1; col < CELL_LENGTH; col++)
        graphField.addEdge(nodeField[col - 1][CELL_WIDTH - 1], nodeField[col][CELL_WIDTH - 1]);

    for (int col = 0; col < FIELD_LENGTH; col++)
        for (int row = 0; row < FIELD_WIDTH; row++)
            coordMap[nodeField[col][row]] = { col, row };
}

void PathSearchField::update() {
    for (int col = 0; col < FIELD_LENGTH; col++)
        for (int row = 0; row < FIELD_WIDTH; row++)
            if (FieldCell &fieldCell = field.get({ col, row }); fieldCell.fieldCellType == FieldCell::FieldCellType::resource)
                nodeFilter[nodeField[col][row]] = false;
            else
                nodeFilter[nodeField[col][row]] = true;
}

std::pair<FieldCoord, bool>  PathSearchField::generatePath(const FieldCoord &source_){
    if (source_ == NONE_FIELD_CELL) {
        return std::make_pair(NONE_FIELD_CELL, false);
    }
    /* if(source_ == FieldCoord { -1, -1 } ) */
    /*     throw "here"; */
    lemon::ListGraph::Node source(nodeField[source_.x][source_.y]);
    FieldCoord destinationCoord = field.basePosition;
    lemon::ListGraph::Node destination(nodeField[destinationCoord.x][destinationCoord.y]);

    lemon::FilterNodes<lemon::ListGraph>::ArcMap<int> lengthMap(subGraphField);
    for (lemon::ListGraph::ArcIt it(graphField); it != lemon::INVALID; ++it)
        lengthMap[it] = 1;
    dijkstra_t<lemon::ListGraph> dijkstra{ subGraphField, lengthMap };
    dijkstra.run(source, destination);

    dijkstra_t<lemon::ListGraph>::Path path{ dijkstra.path(destination) };
    {
        int pathLength = path.length();
		if(pathLength <= 1){
            return std::make_pair(destinationCoord, dijkstra.reached(destination));
        }
        int pathLengthIndex = pathLength - 1;
        dijkstra_t<lemon::ListGraph>::Path::RevArcIt it(path);

        for (; pathLengthIndex > 1; ++it, pathLengthIndex--);
        FieldCoord fieldCoord = getCoord(it);
        return std::make_pair(fieldCoord, true);
    }
}