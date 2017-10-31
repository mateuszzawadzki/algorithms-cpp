#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX = 1000000;
struct edge {
    int u;
    int v;
    int weight;
};

void printResultArrays(int* distances, int* previous, int size);

void solveBellmanFordMatrix(const char* file){
    cout << "Bellman-Ford - matrix representation" << endl;
    ifstream input;
    input.open(file);
    int vertices;
    input >> vertices;
    cout << vertices;
    cout << endl;
    int** array = new int*[vertices];
    for(int i = 0; i < vertices; i++){
        array[i] = new int[vertices];
    }
    while(!input.eof()){
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                input >>array[i][j];
            }
        }
    }
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            cout << array[i][j];
            cout << " ";
        }
        cout << endl;
    }
    input.close();

    int* distances = new int[vertices];
    int* previous = new int[vertices];
    distances[0] = 0;
    previous[0] = -1;
    for(int i = 1; i < vertices; i++) {
        distances[i] = MAX;
        previous[i] = -1;
    }

    for(int n = 1; n < vertices; n++) {
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                if(array[i][j] == 0 || i == j) continue;
                if(distances[j] > distances[i] + array[i][j]){
                    distances[j] = distances[i] + array[i][j];
                    previous[j] = i;
                }
            }
        }
    }
    printResultArrays(distances, previous, vertices);
}

void printResultArrays(int* distances, int* previous, int size) {
    cout << "distances: " << endl;
    for(int i = 0; i < size; i++) {
        cout << distances[i];
        cout << " ";
    }
    cout << endl;

    cout << "previous: " << endl;
    for(int i = 0; i < size; i++) {
        cout << previous[i];
        cout << " ";
    }
    cout << endl;
};

void solveBellmanFordList(const char* file) {
    cout << "Bellman-Ford - list representation" << endl;
    ifstream input;
    input.open(file);
    int vertices;
    input >> vertices;
    cout << vertices;
    cout << endl;

    int u, v, w;
    vector<edge*> list;
    while(!input.eof()){
        input >> u >> v >> w;

        struct edge *e = new edge;
        e->u = u;
        e->v = v;
        e->weight = w;
        list.emplace_back(e);
    }
    input.close();

    for ( auto &e : list ) {
        cout << e->u << " " << e->v << " " << e->weight << endl;
    }

    int* distances = new int[vertices];
    int* previous = new int[vertices];
    distances[0] = 0;
    previous[0] = -1;
    for(int i = 1; i < vertices; i++) {
        distances[i] = MAX;
        previous[i] = -1;
    }

    for(int n = 1; n < vertices; n++) {
        for ( auto &e : list ) {
            if(distances[e->v] > distances[e->u] + e->weight){
                distances[e->v] = distances[e->u] + e->weight;
                previous[e->v] = e->u;
            }
        }
    }

    printResultArrays(distances, previous, vertices);
}

int main( int argc, const char* argv[]){
    solveBellmanFordMatrix("bf\\matrix.txt");
    solveBellmanFordList("bf\\edges.txt");
}




