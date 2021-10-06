//
// Created by Yncrea on 19/04/2021.
//

#include "graph.h"
#include "clique.h"

Clique Graph :: try_to_add_to_clique(Clique S, int vertex){
    Clique c0 = S;
    c0.sommet_clique.push_back(vertex);
    c0.nbr_edge += c0.nbr_vertex;
    c0.nbr_vertex++;

    list<pair<int , int>> listElem;
    c0.adj_list.push_back(listElem);
    c0 = fill_Add_Neighbor(c0, vertex);

    if(c0.is_clique()){
        S.sommet_clique.push_back(vertex);
        S.nbr_edge += S.nbr_vertex;
        S.nbr_vertex++;
        S.adj_list.push_back(listElem);
        S = this->fill_Add_Neighbor(S, vertex);
        S.weight = S.calcul_weight();
    }
    return S;
}
void Graph::supprime(Clique* c, int vertex) {
    int indice_sommet_suppr;

    for (int f = 0; f < c->sommet_clique.size(); f++) {
        if (c->sommet_clique[f] == vertex) {
            indice_sommet_suppr = f;
        }
    }

    int b = 0;
    //On le supprime de la liste des sommets de la clique
    for (vector<int>::iterator it = c->sommet_clique.begin(); it != c->sommet_clique.end(); ++it) {
        b++;
        if (c->sommet_clique[b - 1] == vertex) {//a voir le niveau d'incrementation
            c->sommet_clique.erase(it);
            break;
        }
    }

    int nbEdges_moins = 0;
    int cpt = 0;

    for (auto it = c->adj_list.begin(); it != c->adj_list.end(); ++it) {
        cpt++;
        if (cpt == indice_sommet_suppr + 1) {//a voir le niveau d'incrementation
            nbEdges_moins = it->size();
            c->adj_list.erase(it);
            break;
        }
    }

    //Suppression du sommet des listes de ses voisins qui sont dans la clique
    c->suppr_Sommet_Clique(vertex);
    c->nbr_vertex--;
    c->nbr_edge = c->nbr_edge - nbEdges_moins;
    c->nbr_edge += c->nbr_vertex;
    c->weight = c->calcul_weight();

}

void Graph :: recursive(Clique* clique_max, Clique* c, int vertex) {

    Clique TMP = *c;

    TMP.sommet_clique.push_back(vertex);
    TMP.nbr_edge += c->nbr_vertex;
    TMP.nbr_vertex++;

    list<pair<int, int>> listElem;
    TMP.adj_list.push_back(listElem);
    TMP = fill_Add_Neighbor(TMP, vertex);
    TMP.weight = TMP.calcul_weight();

    // vertex restant POUR LA BRANCHE
    int nbVertexInClique = 0;
    for(auto vertices : this->adj_list[vertex-1]){//les voisins de vertex
        for(auto item : TMP.sommet_clique){
            if(item == vertices.first){
                nbVertexInClique++;
            }
        }
    }

    int vertex_restant = this->adj_list[vertex-1].size() - nbVertexInClique; // dans la branche on peut ajouter max 6 vertex soit
    int edges_restant = 0.5*(vertex_restant-1)*vertex_restant;// soit 1/2 * (n-1)n edges
    int poids_max_potentiel = TMP.weight + edges_restant*100;  // c'est le poid max qua l'on peux trouver dans la branche


    if (clique_max->weight >= poids_max_potentiel) {
        return;
    }

    if (TMP.is_clique()) {
        c->sommet_clique.push_back(vertex);
        c->nbr_edge += c->nbr_vertex;
        c->nbr_vertex++;

        c->adj_list.push_back(listElem);
        *c = fill_Add_Neighbor(*c, vertex);
        c->weight = c->calcul_weight();

        if (c->weight > clique_max->weight) {
            *clique_max = *c;
        }

        for(auto neighbor : this->adj_list[vertex -1]){
            //cout << "\t voisin : "<< neighbor.first << endl;
            if(neighbor.first > vertex){
                recursive(clique_max, c, neighbor.first);
            }
        }
        c->supprime(c, vertex);
    }
}

Clique Graph::algo1() {
    Clique clique;
    Clique cl_final;
    for(int i = 1 ; i < this->nbr_vertex ; i++){
        recursive(&cl_final, &clique, i);
    }
    return cl_final;
}

