//
// Created by Yncrea on 19/04/2021.
//

#ifndef PROJET_GRAPHE_GRAPH_H
#define PROJET_GRAPHE_GRAPH_H

//fonction base cpp
#include <iostream>
#include <cstdlib>
#include <string>

//tableau dynamique et couple
#include <vector>
#include <list>
#include <map>
#include <utility>

//lecture de fichier et de chaine de carac
#include <fstream>
#include <sstream>

//fonction pour
#include <algorithm>
#include <ctime>
#include <cmath>


//truc du futur
//#define INF (unsigned)!((int)0)

using namespace std;
class Graph;
class Clique;
class Vertex_Graph;

class Graph {
protected:
    int nbr_vertex;
    int nbr_edge;
    vector<list<pair<int , int>>> adj_list;
public:
    // ================= CONSTRUCTEUR & DESTRUCTEUR ================
    Graph();
    Graph(int nbr_vertices);
    Graph(string fp);
    ~Graph();


     //============================================================
    // ================= GETTER & SETTER ===========================
    int get_nbr_vextex();
    int get_nbr_edge();
    vector<list<pair<int , int>>> get_adj_list();

    void set_nbr_vertex(int i);
    void set_nbr_edge(int i);
    void set_adj_list(vector<list<pair<int , int>>> adj_list);
    //============================================================
    // ================= OUTILS DE DEBUGG ===========================

    void print_list_n(int n);
    list<pair<int , int>> get_list_n(int n); // return la liste de l'entier n /!\ cela prend en compte le fait qu'on commence notre tableau a i - 1
    //ex : si on veut la list du sommet 1 on dit n == 1 meme si on va regarder adj_list[0] dans le code cela va etre plus simple pour la comprhension du code
    void write_in_file(string input);
    void write_in_list(int x, int y, int w);
    void processing(int value_algo, string input_file, int val_argc);


    //============================================================
    // =================  algo 1 =================================
    Clique algo1();// renvoie la clique max du graph
    void recursive(Clique* clique_max, Clique* c, int vertex);
    Clique try_to_add_to_clique(Clique S, int vertex);
    void supprime(Clique* c, int sommet);

    // ============================================================
    // =================  algo 2 =================================
    Clique algo2();// renvoie la clique max du graph


    // ============================================================
    // =================  algo 3 =================================
    Clique algo3();// renvoie la clique max du graph
    Clique Visit_Neighbor(Clique S, Vertex_Graph start_vertex, vector<int> configuration_vertex);
    Clique fill_Add_Neighbor(Clique S, int num_vertex);
    int getPoids_edge(int indice_List_vertex, int num_second_vertex);

    // ============================================================
    // =================  algo 4 =================================
    Clique algo3(int *tabulist);
    Clique algo4();

    // ============================================================
};

void split(string chaine, char delimiteur, vector<string> *elements);
vector<string> split( string chaine, char delimiteur);
int stringToNumber(string value);
bool check_if_belongs_vector(int u, vector<int> tab);
bool check_if_belongs_neighbor(int u, list<pair<int, int>> tab);

#endif //PROJET_GRAPHE_GRAPH_H
