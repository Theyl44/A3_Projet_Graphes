//
// Created by Yncrea on 22/04/2021.
//
//------------Clique-------------
//constructeur
#include "clique.h"

Clique::Clique() {
//    Graph graph;
    this->nbr_vertex = 0;
    this->nbr_edge = 0;
    this->adj_list.clear();
    this->sommet_clique.clear();
    this->weight=0;
}

//Constructeur de copie
Clique::Clique(Clique const &copie) {
    this->nbr_vertex    = copie.nbr_vertex;
    this->nbr_edge      = copie.nbr_edge;
    this->adj_list      = copie.adj_list;
    this->weight        = copie.weight;
    this->sommet_clique = copie.sommet_clique;
}

//calcul poids clique
int Clique::calcul_weight() {
    int weight = 0;
    for (auto sommet : this->adj_list) {
        for (auto oui : sommet) {
            if (any_of(this->sommet_clique.begin(),this->sommet_clique.end(),[&](const int& elem) { return elem == oui.first; })){
                weight += oui.second;
            }
        }
    }
    return weight/2;
}

void Clique::print_clique() {
    cout << "La clique est composée des sommets suivant : ";
    for (auto item : this->sommet_clique){
        cout << item <<", ";
    }
    cout <<  endl << "Elle a un poids de : " << this->weight << endl;
}
void Clique::write_solution(string input, string methode, int value_argc){

    ofstream myfile;
    string fp = "";
    if(value_argc == 2){
        fp = "../Instances/"+input+"_"+methode+".out";
    }
    myfile.open(fp, ios::out);
    myfile << this->nbr_vertex << " " << this->weight << endl;
    for (auto item : this->sommet_clique){
        myfile << to_string(item)+" ";
    }
    myfile.close();
}


void Clique::suppr_Sommet_Clique(int sommet_a_suppr){
    /*
     * Pour supprimer dans les liste le sommet qui sort de la clique
     */
    int i =0;
    for(i = 0;i<this->adj_list.size();i++){
        for(auto ite = this->adj_list[i].begin();ite!=this->adj_list[i].end(); ++ite ){
            if(ite->first == sommet_a_suppr){
                //si on a trouvé notre element,on supprime l'element, on quitte la liste et on prend la suivante
                this->adj_list[i].erase(ite);
                break;
            }
        }
    }
}
bool Clique :: check_if_exists(int i,int j){
    for(auto item : this->adj_list[i]){
        if(item.first == j){
            return true;
        }
    }
    return false;
}
bool Clique :: is_clique(){
    for(int indiceVertex1 = 0; indiceVertex1 < this->sommet_clique.size();indiceVertex1++){
        for(int indiceVertex2 = 0; indiceVertex2 < this->sommet_clique.size();indiceVertex2++){
            int entierVertex = this->sommet_clique[indiceVertex1];
            int entierVertex2 = this->sommet_clique[indiceVertex2];

            if(entierVertex > entierVertex2  && !check_if_exists(indiceVertex1, entierVertex2)){
                return false;
            }
        }
    }
    return true;
}
