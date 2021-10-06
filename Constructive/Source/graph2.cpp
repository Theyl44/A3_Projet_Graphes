//
// Created by Yncrea on 19/04/2021.
//

#include "graph.h"
#include "clique.h"


bool check_if_belongs_vector(int u, vector<int> tab){
    //cout << "test" << endl;
    for(int i = 0 ; i < tab.size() ; i++){
        //cout<<tab[i]<<endl;
        if(tab[i] == u){
            return true;
        }
    }
    return false;
}


Clique Graph::algo2(){
    int index_max = 0 ;
    for(int i = 0 ; i < this->get_nbr_vextex() ; i++){
        if(this->adj_list[i].size() >= this->adj_list[index_max].size()){
            index_max = i;
        }
    }

    int x = index_max + 1;
    vector<int> Gp;   //subgraph of G
    Gp.push_back(x);

    for(auto item : this->adj_list[index_max]){
        Gp.push_back(item.first);
    }

    Clique c = Clique();
    c.sommet_clique.push_back(x);
    c.nbr_vertex = 1;
    c.adj_list.push_back(this->adj_list[index_max]);

    list<pair<int,int>> list_a_check;
    vector<int> Gp_temp;
    Gp_temp.clear();

    while(Gp.size() != c.sommet_clique.size()){
        int u = c.sommet_clique.back();
        int w_max = 0;
        int index = 0;

        for(auto i : this->adj_list[u - 1]){
            if(!check_if_belongs_vector(i.first, c.sommet_clique) && i.second >= w_max && check_if_belongs_vector(i.first, Gp)){
                w_max = i.second;
                index = i.first;
            }
        }

        c.adj_list.push_back(this->adj_list[index - 1]);
        c.sommet_clique.push_back(index);
        c.nbr_edge += c.nbr_vertex;
        c.nbr_vertex++;
        c.weight = c.calcul_weight();

        list_a_check = adj_list[index - 1];
        Gp_temp.clear();
        Gp_temp.push_back(index);
        for(auto i : list_a_check){
            if(check_if_belongs_vector(i.first,Gp)){
                Gp_temp.push_back(i.first);
            }
        }
        Gp = Gp_temp;
    }
    return c;
}

