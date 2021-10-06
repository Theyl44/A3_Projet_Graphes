//
// Created by Yncrea on 06/05/2021.
//

#include "vertex_Graph.h"

Vertex_Graph::Vertex_Graph() {
    this->name = 0;
    this->vertex_weight = 0;
    this->vertexNotConnected = 0;
    this->addValue = 0;
}

Vertex_Graph::~Vertex_Graph() {}

Vertex_Graph::Vertex_Graph(Vertex_Graph const &copie){
    this->name = copie.name;
    this->vertex_weight  = copie.vertex_weight;
    this->vertexNotConnected = copie.vertexNotConnected;
    this->addValue  = copie.addValue;
}

int Vertex_Graph::getName() const {
    return name;
}

void Vertex_Graph::setName(int name) {
    this->name = name;
}

int Vertex_Graph::getVertexWeight() const {
    return vertex_weight;
}

void Vertex_Graph::setVertexWeight(int vertexWeight) {
    this->vertex_weight = vertexWeight;
}

int Vertex_Graph::getVertexNotConnected() const {
    return vertexNotConnected;
}

void Vertex_Graph::setVertexNotConnected(int vertexNotConnected) {
    this->vertexNotConnected = vertexNotConnected;
}

int Vertex_Graph::getAddValue() const {
    return addValue;
}

void Vertex_Graph::setAddValue(int addValue) {
    this->addValue = addValue;
}

void Vertex_Graph::resetVertex() {
    this->addValue = 0;
    this->name = 0;
    this->vertex_weight = 0;
    this->vertexNotConnected = 0;
}