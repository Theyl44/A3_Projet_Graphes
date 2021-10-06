//
// Created by Yncrea on 22/04/2021.
//


#ifndef PROJET_GRAPHE_CLIQUE_H
#define PROJET_GRAPHE_CLIQUE_H

#include "graph.h"



class Clique : public Graph {
protected:
public:
    //Constructeur pour clique --> heritage
    int weight;
    int calcul_weight();
    vector<int> sommet_clique;

    Clique();
    Clique(Clique const &copie);

    bool is_clique();
    bool check_if_exists(int i,int j);
    void print_clique();
    void write_solution(string input, string methode, int value_argc);  //input = 20_75 par exemple et methode ex) :
                                                                                    // “exact”,
                                                                                    //“constructive”,
                                                                                    //“local_search”
                                                                                    // and “tabu_search”.
    void suppr_Sommet_Clique(int sommet_a_suppr);
};

#endif //PROJET_GRAPHE_CLIQUE_H
