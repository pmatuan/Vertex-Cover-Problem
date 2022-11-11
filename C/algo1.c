/*Lỗi ở hàm CountEdgesOfVertexCover do chưa triển khai ý tưởng dựa trên cgen đc*/


#include "all.c"
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover; 
const int N = 2e6;
int count = 0;
typedef struct pair{
    int x;
    int y;
} pair;

void CountEdgesOfVertexCover(struct gsllist **list, struct hmap *TraversedEdge, int vertex){
    gsl_traverse(cur, list[vertex]){
        int node = (int)cur->l;
        gtype *value = hmap_value(TraversedEdge, gtype_l(vertex));
        if(!value){
            hmap_insert(TraversedEdge, gtype_l(vertex), gtype_l(1));
        }
        else{
            value->l++;   
        }
        hmap_insert(TraversedEdge, gtype_l(vertex), gtype_l(1));

    }
}

void LoadInput(char *inputGraph, char *inputVertexCover, struct gsllist **adj, struct hmap *TraversedEdge){
    FILE *ReadGraph = fopen(inputGraph, "r");
    fscanf(ReadGraph, "%d %d", &NumberOfNodes, &NumberOfEdges);
    /*Chưa cấp phát động*/
    int source, destination;
    while(fscanf(ReadGraph, "%d %d\n", &source, &destination) != EOF){
        gsl_push_back(adj[source], gtype_l(destination));
    }
    fclose(ReadGraph);

    FILE *ReadVertexCover = fopen(inputVertexCover, "r");
    fscanf(ReadVertexCover, "%d\n", &NumberOfVertexCover);
    
    char c;
    int vertex;
    while(fscanf(ReadVertexCover, "%c %d\n", &c, &vertex)!= EOF){
        CountEdgesOfVertexCover(adj, TraversedEdge, vertex);
    }
    fclose(ReadVertexCover);
}


void Output(struct gsllist **adj, struct hmap *TraversedEdge){
    hmap_traverse(key, value, TraversedEdge){
        printf("%ld %ld\n", key->l, value->l);
    }

    // if(NumberOfEdges == hmap_size(TraversedEdge)){
    //     printf("%s\n", "Là tập đỉnh bao phủ");
    // }
    // else{
    //     printf("%s\n", "Không là tập đỉnh bao phủ");
    // }
}
int main(int argc, char* argv[]){
    struct gsllist **adj = calloc(N, sizeof(struct gsllist *));
    for(int i=0; i<N; i++){
        adj[i] = gsl_create_list(NULL);
    }
    struct hmap *TraversedEdge = hmap_create(gtype_hash_l, gtype_cmp_l, NULL, NULL);


    LoadInput(argv[1], argv[2], adj, TraversedEdge);
    Output(adj, TraversedEdge);


    for(int i=0; i<N; i++){
        gsl_free(adj[i]);
    }
    free(adj);
    free(TraversedEdge);
    return 0;
}