//
// Created by Yncrea on 19/04/2021.
//
/*
 * local search heuristic
 */

#include "graph.h"
#include "clique.h"
#include "vertex_Graph.h"


Clique Graph::algo3(){
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
        if (this->adj_list[k].size() >= this->adj_list[v.getName()-1].size()) {
            v.setName((k + 1));
        }
    }

    S.sommet_clique.push_back(v.getName());//ajout de notre sommet dans la liste des sommets de la clique
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
    //ajout d'une liste pour le premier element

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
/*
 * Cette fonction a pour but de faire le tour des voisins de notre clique et de renvoyer alors une clique avec n+1 vertices
 * par rapport a une entrée de n vertices
 *
 * La première étape est l'ajout du "meilleur" vertex
 * La 2nde étape est le swap de 2 vertices
 */
Clique Graph::Visit_Neighbor(Clique S, Vertex_Graph start_vertex, vector<int> configuration_vertex){
    //tableau qui permet de classer les vertex pour l'ajout
    vector<Vertex_Graph> tab_Add;

    //tableau qui permet de classer les vertex pour le swap
    vector<Vertex_Graph> tab_Swap;

    bool valid = true;
    int length_connex = 0;

    int i = 0;
    int j = 0;
    int s = 0;

    Vertex_Graph vertex_Add;
    Vertex_Graph vertex_Swap;
    //-----------Part add a Vertex to the Clique----------
    //On regarde tous les vertices du graphe et on ne choisit que ceux qui sont voisins de la clique mais pas dedans

    /*
     * ====Amélioration a faire====
     * Ne pas prendre tous les vertex du graph mais seulement ceux voisins pour gagner en rapidité
     * Pour cela, on lit seulement les listes des sommets de la clique qui sont dans le graphe
     * Et on prend les éléments qui ne sont pas déjà dans la liste adjacente du sommet mais cette fois-ci dans la clique
     *
     */
    for(auto vert : this->adj_list[start_vertex.getName()-1]){
        if(!check_if_belongs_vector(vert.first, S.sommet_clique)){
            for(auto j : S.sommet_clique){
                //On regarde dans chaque liste de voisins du graphe, pas de la clique, si notre sommet si trouve
                if(!check_if_belongs_neighbor(vert.first, this->adj_list[j-1])){
                    valid = false;
                }
            }
            if(valid){
                //calcul du poids qui entoure le vertex
                Vertex_Graph v;
                v.setName(vert.first);
                v.setVertexWeight(0);
                for(auto a : this->adj_list[v.getName()-1]){
                    v.setVertexWeight(v.getVertexWeight() + a.second);
                }
                tab_Add.push_back(v);
            }
        }
        valid = true;
    }

    //on choisi le vertex avec le meilleur poids, il apporte plus de plus-value a la clique
    for(auto a : tab_Add){
        if(a.getVertexWeight() > vertex_Add.getVertexWeight()){
            vertex_Add = a;
        }else if(a.getVertexWeight() == vertex_Add.getVertexWeight()){
            if(configuration_vertex[a.getName() - 1]==1 && a.getAddValue() > vertex_Add.getAddValue()){
                vertex_Add = a;
            }
        }
    }
    //si on a un sommet à ajouter, sinon on ajoute rien
    if(vertex_Add.getName() > 0){
        //on permet au voisins d'etre éligible pour la clique
        for(auto t : this->adj_list[vertex_Add.getName()-1]){
            configuration_vertex[t.first -1] = 1;
        }
        //ajout du vertex dans le graphe de la clique
        S.sommet_clique.push_back(vertex_Add.getName());
        int indiceElemAdd = S.sommet_clique.size();

        //creation de liste de notre nouveau sommet et ajout dans la clique ainsi que l'ajout de ce vertex
        // dans les autres listes avec le poids associé
        list<pair<int , int>> pairAdd;
        S.adj_list.push_back(pairAdd);
        S = this->fill_Add_Neighbor(S, vertex_Add.getName());

        //update du poids, du nombres d'eges et du nombre de vertices
        S.nbr_edge +=S.nbr_vertex;
        S.nbr_vertex++;
        S.weight = S.calcul_weight();
    }



    //---------Part Swap a vertex in the clique---------------
    //comme le swap ptet des modifs et améliorations a effectuer au niveau du 1er for, pour éliminer des nombreuses itérations


    for(auto vert : this->adj_list[start_vertex.getName()-1]){
//    for(s = 0;s<this->adj_list.size();s++){
        //On regarde si notre vertex n'est pas deja dans la clique
        if(!check_if_belongs_vector(vert.first, S.sommet_clique)) {
            Vertex_Graph p;
            p.setName(vert.first);
            //Pour chaque sommet, on regarde s'il se trouve dans la clique
            for (auto som : S.sommet_clique) {
                if (check_if_belongs_neighbor(vert.first, this->adj_list[som - 1])) {
                    length_connex++;
                } else {
                    vertex_Swap.setName(som);
                }
            }
            //si notre vertex est connecté a tous les autres vertex de la clique sauf 1,
            //on note le vertex qui va etre exempté

            if (length_connex == S.sommet_clique.size() - 1) {
                p.setVertexNotConnected(vertex_Swap.getName());

                //calcul weight p et calcul weight vertex_Swap
                for (auto a: this->adj_list[p.getName() - 1]) {
                    p.setVertexWeight(p.getVertexWeight() + a.second);
                }
                for (auto a: this->adj_list[vertex_Swap.getName() - 1]) {
                    vertex_Swap.setVertexWeight(vertex_Swap.getVertexWeight() + a.second);
                }
                //calcul du gain de poids entre le nouveau vertex et l'ancien
                p.setAddValue(p.getVertexWeight() - vertex_Swap.getVertexWeight());
                tab_Swap.push_back(p);
            }
            //reset de value pour refaire cette etape pour chaque vertex
            length_connex = 0;
            vertex_Swap.resetVertex();
        }
    }
    //On choisi le vertex avec le meilleur poids,
    //si 2 vertex on le meme poids, on prend celui avec le meilleur gain et qui est possible de prendre
    //si 2 vertex, on tous d'egaux, on va garder le 1er, evite le constructeur de copie
    for(auto n : tab_Swap){
        if(n.getVertexWeight() >= vertex_Swap.getVertexWeight() && configuration_vertex[n.getName() - 1]==1 && n.getAddValue() > vertex_Swap.getAddValue()){
            vertex_Swap = n;
        }
    }
    //si on a pas de sommet nul, qu'il existe bien
    if(vertex_Swap.getName() > 0){

        int indice_sommet_suppr;
        for(int f = 0; f<S.sommet_clique.size();f++){
            if(S.sommet_clique[f] == vertex_Swap.getVertexNotConnected()){
                indice_sommet_suppr = f;
            }
        }

        int b = 0;
        //On le supprime de la liste des sommets de la clique
        for(vector<int>::iterator it=S.sommet_clique.begin(); it!=S.sommet_clique.end(); ++it){
            b++;
            if(S.sommet_clique[b-1] == vertex_Swap.getVertexNotConnected()){//a voir le niveau d'incrementation
                S.sommet_clique.erase(it);
                break;
            }
        }

        //ne peut plus etre utilisé, sauf si un des ses voisins arrive dans la clique
        configuration_vertex[vertex_Swap.getVertexNotConnected()-1] = 0;
        for(auto t : this->adj_list[vertex_Swap.getVertexNotConnected() - 1]){
            configuration_vertex[t.first -1] = 1;
        }

        //Suppression de liste des voisins du sommet a enlever de la clique
        int nbEdges_moins = 0;

        int cpt = 0;
        for(auto it=S.adj_list.begin(); it!=S.adj_list.end(); ++it){
            cpt++;
            if(cpt == indice_sommet_suppr+1){//a voir le niveau d'incrementation
                nbEdges_moins = it->size();
                S.adj_list.erase(it);
                break;
            }
        }

        //Suppression du sommet des listes de ses voisins qui sont dans la clique
        int sommet_poubelle = vertex_Swap.getVertexNotConnected();
        S.suppr_Sommet_Clique(sommet_poubelle);

        S.nbr_vertex--;

        //Le sommet supprimé est remplacé par le nouveau sommet
        S.sommet_clique.push_back(vertex_Swap.getName());

        //on créé sa liste
        list<pair<int , int>> pairSwap;
        S.adj_list.push_back(pairSwap);
        //ajout de ce nouveau vertex dans la liste de chaque voisin
        S = this->fill_Add_Neighbor(S, vertex_Swap.getName());

        //update du poids, des edges et dess vertices
        S.nbr_edge = S.nbr_edge - nbEdges_moins;
        S.nbr_edge += S.nbr_vertex;
        S.nbr_vertex++;
        //retirer le nombre d'edge et rajouter le nombre d'edge gagner
        S.weight = S.calcul_weight();
    }

//renvoie la clique trouvé
    return S;
}