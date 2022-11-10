#include<bits/stdc++.h>
using namespace std;

const int N = 2e6; // Số đỉnh của 3 bài < 2 triệu, nên khai báo như này để đỡ cấp phát động
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover; 
list<int> adj[N]; // danh sách kề
set<int> V; // tập toàn bộ đỉnh
set<int> S; // tập đỉnh bao phủ
set<int> T; // tập V - S

void LoadInput(char *inputGraph, char *inputVertexCover){
    // Load tập cạnh
    ifstream Graph(inputGraph);
    Graph >> NumberOfNodes >> NumberOfEdges;
    int source, destination;
    while(Graph >> source >> destination){
        adj[source].push_back(destination);
        V.insert(source);
    }
    Graph.close();

    // Load tập đỉnh bao phủ cần kiểm tra
    ifstream VertexCover(inputVertexCover);
    VertexCover >> NumberOfVertexCover;
    char c;
    int vertex;
    while(VertexCover >> c >> vertex){
        S.insert(vertex);
    }
    VertexCover.close();
}

void CreateT(){
    // So sánh tự viết và sử dùng set_difference, thấy set_difference nhanh hơn khoảng 1s

    /*
    for(set<int>::iterator it = V.begin(); it != V.end(); it++){
        if(!S.count(*it)){
            T.insert(*it);
        }
    }
    */
    set_difference(begin(V), end(V),
                   begin(S), end(S),
                   inserter(T, end(T)));
}

// Kiểm tra S có phải tập đỉnh bao phủ k
bool check(){ 
    for(set<int>::iterator it = T.begin(); it != T.end(); it++){
        int VertexCurrent = *it;
        list<int> AdjVertexCurrent = adj[VertexCurrent];
        for(list<int>::iterator it1 = AdjVertexCurrent.begin(); it1 != AdjVertexCurrent.end(); it1++){
            int node = *it1;
            if(T.count(node)) return false;
        }
    }
    return true;
}

void Output(){
    bool isVertexCover = check();

    if(isVertexCover){
        cout << "Là tập đỉnh bao phủ" << endl;
    }
    else{
        cout << "Không là tập đỉnh bao phủ" << endl;
    }
}
int main(int argc, char* argv[]){
    LoadInput(argv[1], argv[2]);
    CreateT();
    Output();
    return 0;
}