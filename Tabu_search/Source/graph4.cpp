//
// Created by Yncrea on 19/04/2021.
//
#include "graph.h"
#include "clique.h"
#include "vertex_Graph.h"
Clique Graph::algo3(int*tabulist) {
    /*
     * Cet algo a pour but d'effectuer une recherche par local search, on se sert des voisins des elements courants de la clique
     * pour améliorer notre clique
     */
    Clique S;
    Clique TMP_S;
    vector<int> configuration_vertex; //pour dire si on peut utiliser un vertex ou non
    int k = 0;
    bool arret = false;
    /*
     * La classe vertex_Graph contient tous les elements indispensable pour faire un local search
     * ...Partie Add et Swap...
     * name --> numero du vertex
     * vertex_weight --> poids total de tous les edges reliés a ce sommet
     *
     * ...Partie Swap...
     *  vertexNotConnected --> contient le numero du vertex qui n'est pas relié a notre vertex courant
     *  addValue --> gain d'un vertex --> poids de notre vertex - poids du vertex qui est pas relié
     *
    */
    Vertex_Graph v;
    Vertex_Graph T;


    //Pour créer notre clique on choisi arbitrairement le 1er vertex et on va prendre ensuite le vertex avec une taille max
    v.setName(1);

    //On initialise notre tableau de configuration qui permet de choisir un vertex ou non en fonction de l'indice --> 0 ou 1
    for (k = 0; k < this->adj_list.size(); k++) {
        configuration_vertex.push_back(1);
        if (this->adj_list[k].size() >= this->adj_list[v.getName() - 1].size()&&tabulist[k]!=k+1) {// detecter si on prend rien
            v.setName((k + 1));
        }
    }
    tabulist[v.getName()-1]=v.getName();
    S.sommet_clique.push_back(v.getName());// ajouter ici une sauvegarde du sommet de départ

    //ajout de notre sommet dans la liste des sommets de la clique
    //ajout d'un sommet et de sa liste --> Cette derniere est vide de base car pas d'autres edges
    //On créer sa liste que l'on push ensuite dans le tableau (vector) des listes

    /*
     * -----------Liste d'un vertex--------------
     *
     * pair<int, vector<pair<int,int>>>
     *      1er element pair<int, vector<...>>
     *      le int correspond a la valeur / numero du vertex
     *
     *      le vector correspond à :
     *          vector<pair<int,int>>
     *          Le vector sert a stocker la liste des voisins du sommet
     *          le premier élément sera le vertexOut et le second element sera le poids de l'edge qui relie les 2 vertices
     */

    list<pair<int , int>> pairIn;
    S.adj_list.push_back(pairIn);

    //on n'oublie d'update les values de vertices et de weight
    S.nbr_vertex++;
    S.weight = 0;

    if(this->nbr_edge > 0){
        //le 2 eme sommet ( T ) choisi et celui qui est le 1er de la liste de notre seul sommet de la clique
        T.setName(this->adj_list[v.getName() - 1].begin()->first);
        //on prend le poids entre ces 2 edges
        int weight = this->adj_list[v.getName() - 1].begin()->second;

        //Incrementation du nombre de vertex et d'edges
        S.nbr_edge +=S.nbr_vertex;
        S.nbr_vertex++;

        //ajout du vertex a liste des sommets
        S.sommet_clique.push_back(T.getName());

        //ajout de la liste du second sommet
        list<pair<int , int>> pairOut;
        S.adj_list.push_back(pairOut);
        S.adj_list[1].push_back(make_pair(v.getName(), weight));


        //comme on a ajouter un vertex, il faut ajouter l'edge associé dans la liste des voisins de notre 1er élément
        S.adj_list[0].push_back(make_pair(T.getName(), weight));

        //calcul du poids total de notre clique
        S.weight = S.calcul_weight();

        //1ere solution avec un vertex qui est connecté a tous les elems et un second qui est le 1er dans la liste des voisins du 1er vertex
        TMP_S = S;

    }else{
        arret = true;
    }


    //Boucle qui permet de donner une nouvelle clique tant que celle-ci est meilleure que l'ancienne, sinon arret boucle
    while (!arret) {
        TMP_S = Visit_Neighbor(TMP_S, v, configuration_vertex);
        if (TMP_S.weight > S.weight) {
            S = TMP_S;
        } else {
            arret = true;
        }
    }
    return S;
}


Clique Graph::algo4() {// trouver un moyen de pas retomber sur les cliques déja trouver
    // la majeure "différence" avec l'algo3 est le faite que l'on ai rajouté pendant la recherche du premier sommet,
    // une condition lié a la tabuliste qui nous empeche de relancer l'algo 3 avec le meme premier sommet
    int tabulist[this->nbr_vertex];
    Clique test;
    int boucle=0;
    int iteration=0;
    Clique result = Clique();
    while(boucle<100&&iteration<500)// on fait un nombre x d'itération (surement un calcul a optimisé pour trouver le bon nombre d'itération),
        // si pendant y valeur on a retourné une clique de meme poid on arrete avant d'avoir atteind le nombre d'itération max
    {
        iteration++;
        test = this->algo3(tabulist);
        if (test.weight>result.weight){// on regarde si le resultat du nvx algo3 est meilleur que l'ancien si oui on met la nouvelle valeur dans result
            result=test;
            boucle=0;//nouvelle meilleure clique on reset la valeur de la boucle
        }
        else {
            boucle++;//meme poid donc on ajoute un a la boucle
        }
    }
    int douze;
    return result;
}

