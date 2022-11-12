#include "all.c"
int NumberOfNodes, NumberOfEdges, NumberOfVertexCover, count = 0; 
const int N = 2e6;
struct gsllist **adj;
struct hset **TraversedEdge;
void CountEdgesOfVertexCover(int vertex){
    gsl_traverse(cur, adj[vertex]){
        int node = (int)cur->l;
        int check = hset_contains(TraversedEdge[vertex], gtype_l(node));
        if(!check){
            hset_insert(TraversedEdge[vertex], gtype_l(node));
            hset_insert(TraversedEdge[node], gtype_l(vertex));
            count++;
        }
    }
}

void LoadInput(char *inputGraph, char *inputVertexCover){
    FILE *ReadGraph = fopen(inputGraph, "r");
    fscanf(ReadGraph, "%d %d", &NumberOfNodes, &NumberOfEdges);
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
        CountEdgesOfVertexCover(vertex);
    }
    fclose(ReadVertexCover);
}



void Output(){
    if(NumberOfEdges/2 == count){
        printf("%s\n", "Là tập đỉnh bao phủ");
    }
    else{
        printf("%s\n", "Không là tập đỉnh bao phủ");
    }
}
int main(int argc, char* argv[]){
    adj = calloc(N, sizeof(struct gsllist *));
    TraversedEdge = calloc(N, sizeof(struct hset *));
    for(int i=0; i<N; i++){
        adj[i] = gsl_create_list(NULL);
        TraversedEdge[i] = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    }


    LoadInput(argv[1], argv[2]);
    Output(adj);


    for(int i=0; i<N; i++){
        gsl_free(adj[i]);
        hset_free(TraversedEdge[i]);
    }
    free(TraversedEdge);
    free(adj);
    return 0;
}