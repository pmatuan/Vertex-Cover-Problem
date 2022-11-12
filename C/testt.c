/*Lỗi cấp phát bộ nhớ, dòng 65*/

#include "all.c"
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover; 
const int N = 2e6;
struct gsllist **adj;
struct hset *V;
struct hset *S;
struct hset *T;

void LoadInput(char *inputGraph, char *inputVertexCover){
    FILE *ReadGraph = fopen(inputGraph, "r");
    fscanf(ReadGraph, "%d %d", &NumberOfNodes, &NumberOfEdges);
    /*********************************************************/
    /*Vấn đề nằm ở cấp phát chỗ này*/
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
    struct hset *T = CreateT();
    Output();

    // for(int i=0; i<N; i++){
    //     gsl_free(adj[i]);
    // }
    // free(adj);
    // hset_free(V);
    // hset_free(S);
    // hset_free(T);
    return 0;
}