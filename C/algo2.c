/*Lỗi cấp phát bộ nhớ, dòng 15*/

#include "all.c"
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover; 
const int N = 2e6;
struct gsllist **adj;
struct hset *V;
struct hset *S;
struct hset *T;
/*
    file .txt bao gồm số lượng đỉnh và số lượng cạnh, tiếp theo là tập đỉnh nguồn đến đích
    file .vc bao gồm số lượng đỉnh bao phủ, tiếp theo là các đỉnh bao phủ

    Lưu đồ thị theo danh sách kề: tạo mảng các gsl để lưu, trong đó gsl[i] là danh sách kề của đỉnh i.
    Nếu theo logic này thì em chỉ cần tạo mảng gsl với NumberOfNodes phần tử. Nhưng như thế bị báo lỗi.
    Thầy xem giúp em ạ
*/
void LoadInput(char *inputGraph, char *inputVertexCover){
    FILE *ReadGraph = fopen(inputGraph, "r");
    fscanf(ReadGraph, "%d %d", &NumberOfNodes, &NumberOfEdges);
    /*********************************************************/
    /*Vấn đề nằm ở cấp phát chỗ này*/
    /*Nếu thay NumberOfNodes = N = 2e6 thì chạy được với bộ dữ liệu nhỏ*/
    adj = calloc(N, sizeof(struct gsllist *));
    /*********************************************************/
    for(int i=0; i<N; i++){
        adj[i] = gsl_create_list(NULL);
    }
    int source, destination;
    V = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    while(fscanf(ReadGraph, "%d %d\n", &source, &destination) != EOF){
        gsl_push_back(adj[source], gtype_l(destination));
        hset_insert(V, gtype_l(source));
    }
    fclose(ReadGraph);

    FILE *ReadVertexCover = fopen(inputVertexCover, "r");
    fscanf(ReadVertexCover, "%d\n", &NumberOfVertexCover);
    
    char c;
    int vertex;
    S = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    while(fscanf(ReadVertexCover, "%c %d\n", &c, &vertex)!= EOF){
        hset_insert(S, gtype_l(vertex));
    }
    fclose(ReadVertexCover);
}

struct hset * CreateT(){
    struct hset *T = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    hset_traverse(key, V){
        if(hset_index_of(S, gtype_l(key->l)) == -1){
            hset_insert(T, gtype_l(key->l));
        }
    }
    return T;
}
bool check(){
    hset_traverse(key, T){
        int VertexCurrent = (int)key->l;
        struct gsllist *AdjVertexCurrent = adj[VertexCurrent];
        gsl_traverse(cur, AdjVertexCurrent){
            int node = (int)cur->l;
            if(hset_index_of(T, gtype_l(node)) != -1){
                return false;
            }
        }
    }
    return true;
}

void Output(){
    bool isVertexCover = check(adj, T);

    if(isVertexCover){
        printf("%s\n", "Là tập đỉnh bao phủ");
    }
    else{
        printf("%s\n", "Không là tập đỉnh bao phủ");
    }
}
int main(int argc, char* argv[]){

    LoadInput(argv[1], argv[2]);
    T = CreateT();
    Output();

    for(int i=0; i<N; i++){
        gsl_free(adj[i]);
    }
    free(adj);
    hset_free(V);
    hset_free(S);
    hset_free(T);
    return 0;
}