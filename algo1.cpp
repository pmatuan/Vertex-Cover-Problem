#include<bits/stdc++.h>
using namespace std;

#define pair_ii pair<int,int>

const int N = 2e6; // Số đỉnh của 3 bài < 2 triệu, nên khai báo như này để đỡ cấp phát động
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover, edges = 0; 
vector<int> adj[N+1]; // danh sách kề
set<pair_ii> TraversedEdge;


void CountEdgesOfVertexCover(int vertex){
    for(int i = 0; i < adj[vertex].size(); i++) {
        int node = adj[vertex][i];
        if(!TraversedEdge.count(pair_ii(vertex, node))) {
            edges++;
            TraversedEdge.insert(pair_ii(vertex, node));
            TraversedEdge.insert(pair_ii(node, vertex));
        }
    }
}


void LoadInput(char *inputGraph, char *inputVertexCover){
    // Load tập cạnh
    ifstream Graph(inputGraph);
    Graph >> NumberOfNodes >> NumberOfEdges;
    int source, destination;
    while(Graph >> source >> destination){
        adj[source].push_back(destination);
    }
    Graph.close();

    // Load tập đỉnh bao phủ cần kiểm tra
    ifstream VertexCover(inputVertexCover);
    VertexCover >> NumberOfVertexCover;
    char c;
    int vertex;
    while(VertexCover >> c >> vertex){
        CountEdgesOfVertexCover(vertex);
    }
    VertexCover.close();
}


void Output(){
    if(NumberOfEdges/2 == edges){
        cout << "Là tập đỉnh bao phủ" << endl;
    }
    else{
        cout << "Không là tập đỉnh bao phủ" << endl;
    }
}


int main(int argc, char *argv[]){
    LoadInput(argv[1], argv[2]);
    Output();
}