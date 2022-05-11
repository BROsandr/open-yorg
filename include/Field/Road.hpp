#pragma once

#include <lemon/dijkstra.h>
#include <lemon/list_graph.h>

#include "ValuesAndTypes.hpp"
#include "Field/Graph.hpp"
#include "lemon/adaptors.h"

class FieldCell;

class Road: public Graph<lemon::ListDigraph>{
public:
    Road(Field &field);
    void update() override;
    void draw();
    std::pair<FieldCoord, bool> generatePath(const FieldCoord &source, ResourceType type);
    bool mineHasResource(const FieldCoord &source, ResourceType type);
    void showFutureRoad();
    void showRealRoad(bool revert = true);
    bool isFutureCell(FieldCoord &fieldCoord);

private:
    void connect(lemon::ListDigraph::NodeIt node);
    void drawArc(lemon::FilterNodes<lemon::ListDigraph>::ArcIt arcIt);
    bool canConnect(FieldCoord leftCoord, FieldCoord rightCoord);
    lemon::ListDigraph::NodeMap<bool> nodeFilterFuture{ graphField};
    lemon::FilterNodes<lemon::ListDigraph> futureSubGraphField{ graphField, nodeFilterFuture};
    bool isFutureArc(lemon::ListDigraph::Node &source, lemon::ListDigraph::Node &target);
};