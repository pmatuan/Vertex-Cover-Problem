#include<bits/stdc++.h>
using namespace std;

const int N = 2e6; // Số đỉnh của 3 bài < 2 triệu, nên khai báo như này để đỡ cấp phát động
int NumberOfNodes, NumberOfVertexCover, u, v; 
list<int> adj[N+6]; // danh sách kề
set<int> V; // tập toàn bộ đỉnh
set<int> S; // tập đỉnh bao phủ
set<int> T; // tập V - S

void LoadInput(char *input, char *input1){
    // Load tập cạnh
    ifstream inp(input);
    inp >> NumberOfNodes;
    while(inp >> u >> v){
        adj[u].push_back(v);
        V.insert(u);
    }
    inp.close();

    // Load tập đỉnh bao phủ cần kiểm tra
    ifstream inp1(input1);
    inp1 >> NumberOfVertexCover;
    char c;
    while(inp1 >> c >> v){
        S.insert(v);
    }
    inp1.close();
}

void CreateT(){
    for(set<int>::iterator it = V.begin(); it != V.end(); it++){
        if(!S.count(*it)){
            T.insert(*it);
        }
    }
}

// Kiểm tra S có phải tập đỉnh bao phủ k
bool check(){ 
    for(set<int>::iterator it = T.begin(); it != T.end(); it++){
        int VertexCurrent = *it;
        list<int> AdjVertexCurrent = adj[VertexCurrent];
        for(list<int>::iterator it1 = AdjVertexCurrent.begin(); it1 != AdjVertexCurrent.end(); it1++){
            int vertex = *it1;
            if(T.count(vertex)) return false;
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