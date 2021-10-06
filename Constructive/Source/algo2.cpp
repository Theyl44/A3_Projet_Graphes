//
// Created by Yncrea on 13/05/2021.
//
#include "graph.h"
#include "clique.h"

int main(int argc, char** argv){
    if(argc != 2){
        cout <<"wrong utilisation of the algo :("<<endl;
        cout <<"read the file readme.txt"<<endl;
        return 0;
    }

    string input_file = argv[1];
    string fp;
    string name = "exact";

    clock_t temps_initial; /* Temps initial en micro-secondes */
    clock_t temps_final; /* Temps final en micro-secondes */
    double temps_cpu; /* Temps total en secondes */

    fp = "../instances/"+input_file+".in";
    Graph g0 = Graph(fp);

    temps_initial = clock ();
    Clique c0 = g0.algo2();
    temps_final = clock();



    c0.print_clique();
    c0.write_solution(input_file, name, argc); //TODO Voir val argc
    temps_cpu = (temps_final - temps_initial) *1e-6;
    cout << "temps pris : "<< temps_cpu << " secondes" << endl;

    return 0;
}