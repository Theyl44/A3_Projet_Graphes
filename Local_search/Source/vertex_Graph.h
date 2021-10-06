//
// Created by Yncrea on 06/05/2021.
//

#ifndef PROJET_GRAPHE_VERTEX_GRAPH_H
#define PROJET_GRAPHE_VERTEX_GRAPH_H


class Vertex_Graph{
protected:
    int name;
    int vertex_weight;
    int vertexNotConnected;
    int addValue;

public:
    Vertex_Graph();
    ~Vertex_Graph();
    Vertex_Graph(Vertex_Graph const &copie);

    int getName() const;

    void setName(int name);

    int getVertexWeight() const;
    void setVertexWeight(int vertexWeight);
    int getVertexNotConnected() const;
    void setVertexNotConnected(int vertexNotConnected);
    int getAddValue() const;
    void setAddValue(int addValue);
    void resetVertex();
};

#endif //PROJET_GRAPHE_VERTEX_GRAPH_H
