//
// Created by Yncrea on 20/04/2021.
//
#include "graph.h"
#include "clique.h"

Graph::Graph(string fp) {
    fstream my_file;
    my_file.open(fp, ios::in);
    int vertexIn;
    int vertexOut;
    int weightEdge;
    vector<string> lineSplit;

    if (!my_file) {
        cout << "No such file :(";
    } else {
        string ligne;
        int i = 1;
        while (getline(my_file, ligne)) {
            if (i == 1) {//Si premiere ligne du fichier
                lineSplit = split(ligne, ' ');
                //on enregistre le nombre de edges et de vertices qu'on a et on init notre this->list pour tous les vertex a null
                this->nbr_vertex = stringToNumber(lineSplit[0]);
                this->nbr_edge = stringToNumber(lineSplit[1]);

                for (int k = 0; k <= nbr_vertex-1; k++) {
                    this->adj_list.emplace_back();
                }
            } else {//i-1 l'indice de notre vertex
                lineSplit = split(ligne, ' ');

                vertexIn = stringToNumber(lineSplit[0]);
                vertexOut = stringToNumber(lineSplit[1]);
                weightEdge = stringToNumber(lineSplit[2]);

                //ajout d'un élément a sa liste
                //on met le vertex dans la liste du vertex d'entree et de sortie
                this->adj_list[vertexIn-1].push_back(make_pair(vertexOut, weightEdge));
                this->adj_list[vertexOut-1].push_back(make_pair(vertexIn, weightEdge));

            }
            if (my_file.eof()) {
                break;
            }
            i++;
        }
    }
    my_file.close();
}

Graph::~Graph() {

}

void split(string chaine, char delimiteur, vector<string> *elements) {
    stringstream ss(chaine);//comprendre le stringstream
    string sousChaine;
    while (getline(ss, sousChaine, delimiteur)) {
        elements->push_back(sousChaine);
    }
}

int stringToNumber(string value) {
    int number = 0;
    istringstream iss(value);
    // convertir en un int

    iss >> number;
    return number;
}

vector<string> split(string chaine, char delimiteur) {
    vector<string> elements;
    split(chaine, delimiteur, &elements);
    return elements;
}
void Graph:: set_nbr_vertex(int i){
    this->nbr_vertex = i;
}
void Graph:: set_nbr_edge(int i ){
    this->nbr_edge = i;
}
void  Graph:: set_adj_list(vector<list<pair<int , int>>> adj_list){
    this->adj_list = adj_list;
}
Graph::Graph() {
    this->nbr_vertex = 5;
    this->nbr_edge = 5;


    // ====== list 1 pour le sommet 1 ============

    pair<int, int> pair1;
    pair1 = make_pair(2, 6);

    list<pair<int, int>> list1;
    list1.push_back(pair1);

    // ====== list 2 pour sommet 2 ===========

    pair<int, int> pair6;
    pair6 = make_pair(1, 6);
    pair<int, int> pair2;
    pair2 = make_pair(3, 2);
    pair<int, int> pair3;
    pair3 = make_pair(4, 3);

    list<pair<int, int>> list2;
    list2.push_back(pair6);
    list2.push_back(pair2);
    list2.push_back(pair3);

    // ====== list 3 pour sommet 3 ===========

    pair<int, int> pair4;
    pair4 = make_pair(2, 2);
    pair<int, int> pair7;
    pair7 = make_pair(4, 5);
    pair<int, int> pair5;
    pair5 = make_pair(5, 4);

    list<pair<int, int>> list3;
    list3.push_back(pair4);
    list3.push_back(pair7);
    list3.push_back(pair5);


    // ====== list 4 pour sommet 4 ===========

    pair<int, int> pair8;
    pair8 = make_pair(2, 3);
    pair<int, int> pair9;
    pair9 = make_pair(3, 5);

    list<pair<int, int>> list4;
    list4.push_back(pair8);
    list4.push_back(pair9);

    // ====== list 5 pour sommet 5 ===========

    pair<int, int> pair10;
    pair10 = make_pair(3, 4);
    list<pair<int, int>> list5;
    list5.push_back(pair10);

//    list<pair<int, int>> list0;
//
//    this->adj_list.push_back(list0);
    this->adj_list.push_back(list1);
    this->adj_list.push_back(list2);
    this->adj_list.push_back(list3);
    this->adj_list.push_back(list4);
    this->adj_list.push_back(list5);
}
int Graph:: get_nbr_vextex(){
    return this->nbr_vertex;
}
Graph::Graph(int nbr_vertices) {
    this->nbr_vertex = nbr_vertices;
    this->nbr_edge = 0;
    for(int i = 0 ; i< nbr_vertices ; i++){
        this->adj_list.emplace_back();
    }
}
int Graph:: get_nbr_edge(){
    return this->nbr_edge;
}
vector<list<pair<int , int>>> Graph:: get_adj_list(){
    return this->adj_list;
}

list<pair<int , int>> Graph:: get_list_n(int n){
    return this->adj_list[n-1];
}
void Graph::print_list_n(int n) {
    list<pair<int , int>> list_to_print = this->get_list_n(n);
    cout<<"liste de ["<<n<<"] : "<<endl;
    for(list<pair<int , int>>::iterator it = list_to_print.begin() ; it != list_to_print.end() ; it ++){
        cout<<"y = "<< it->first << " avec w = " << it->second << endl;
    }
}
void Graph::write_in_file(string input) {
    ofstream myfile;
    string file_name ="Instances/"+input+".in";
    myfile.open(file_name, ios::out);
    myfile << this->nbr_vertex << " "<<this->nbr_edge<<endl;
    for(int i = 0 ; i < this->nbr_vertex ; i++){
        list<pair<int , int>> list_to_print = this->get_list_n(i+1);
        for(list<pair<int , int>>::iterator it = list_to_print.begin() ; it != list_to_print.end() ; it ++){
            if(i < it->first){
                myfile <<i+1<<" "<<it->first<<" "<<it->second<<endl;
            }
        }
    }
    myfile.close();
}

void Graph::write_in_list(int x, int y, int w) {
    this->adj_list[x-1].push_back(make_pair(y,w));
    this->adj_list[y-1].push_back(make_pair(x,w));
}


int Graph::getPoids_edge(int indice_List_vertex, int num_second_vertex){/*
 * Pour recuperer le poids d'un edge situé entre 2 vertex
 */
    int poids = 0;

    //On cherche dans la liste des voisins de notre premier sommet
    //la valeur envoyé est l'indice, il ne reste plus qu'a mettre cette valeur
    //on cherche alors dans les voisins, notre elem et la distance qui est associé
    for(auto i : this->adj_list[indice_List_vertex]){
        if(i.first == num_second_vertex){
            poids = i.second;
        }
    }
    return poids;
}

Clique Graph::fill_Add_Neighbor(Clique S, int num_vertex){
    /*
     * Ajouter notre vertex dans chacune des listes des autres vertex
     * car si ajout, c'est que le nouveau vertex est relié a chaque vertex
     */

    //ajout des distances et des vertex out dans la clique
    int i=0;
    for(i=0; i<S.sommet_clique.size()-1;i++){
        //pour chaque element de la clique, sauf le dernier element ajouté --> celui qu'on veut relie aux autres
        //on prend chaque sommet
        int value_sommet = S.sommet_clique[i];

        //on recupere l'indice de notre vertex situé dans le  graphe de la clique qui servira de liste
        int indice_value_sommet_clique = i; // indice = deja en -1 par rapport a la vrai value

        //on recupere l'indice de notre vertex situé dans le  graphe de la clique qu'on veut ajouter dans les listes
        int indice_value_sommet_clique_list_Second_Elem = S.sommet_clique.size()-1;

        //on recupere l'indice du vertex d'entrée mais cette fois-ci au niveau du graphe
        int indice_value_sommet_Graphe = value_sommet - 1;

        //On recupere alors le poids de notre edge situé entre nos 2 vertices
        int poids = this->getPoids_edge(indice_value_sommet_Graphe, num_vertex);

        //on ajoute dans clique
        if(poids > 0){//si edge existe
            //il y a donc ajout dans la liste du vertex in et dans la liste du vertex out
            S.adj_list[indice_value_sommet_clique].emplace_back(num_vertex,poids);
            S.adj_list[indice_value_sommet_clique_list_Second_Elem].emplace_back(value_sommet,poids);
        }
    }
    return S;
}

bool check_if_belongs_neighbor(int u, list<pair<int, int>> tab){
    /*
     * Pour un vertex, on regarde s'il se trouve dans la liste des voisins de notre clique
     * true si oui et false sinon
     */
    for(auto i : tab){
        if(i.first == u){
            return true;
        }
    }
    return false;
}












































