#include<stdio.h>
#include "cgen/all.h"

const int N = 2e6;
struct gsllist **AdjLists;
struct hset *Vertices;
struct hset *VertexCover;
struct hset *T;
int NumberOfNodes, NumberOfEdges, SizeOfVertexCover;

void Parse_Input(char *graph, char *vc) {
    FILE *Graph = fopen(graph, "r");
    fscanf(Graph, "%d %d\n", &NumberOfNodes, &NumberOfEdges);
    
    AdjLists = calloc(N, sizeof(struct gsllist *));
    for(int i = 0; i < N; i++) {
        AdjLists[i] = gsl_create_list(NULL);
    }
    
    int source, sink;
    Vertices = hset_create(gtype_hash_l, gtype_cmp_l, NULL);

    while (fscanf(Graph, "%d %d\n", &source, &sink) != EOF) {
        hset_insert(Vertices, gtype_l(source));        
        gsl_push_back(AdjLists[source], gtype_l(sink));
    }

    fclose(Graph);

    FILE *VC = fopen(vc, "r");
    fscanf(VC, "%d\n", &SizeOfVertexCover);

    char c;
    int vertex;
    VertexCover = hset_create(gtype_hash_l, gtype_cmp_l, NULL);

    while (fscanf(VC, "%c %d\n", &c, &vertex) != EOF) {
        hset_insert(VertexCover, gtype_l(vertex));
    }
    
    fclose(VC);
}

void CreateT(){
    T = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    
    hset_traverse(key, Vertices) {
        if (hset_index_of(VertexCover, gtype_l(key->l)) == -1) {
            hset_insert(T, gtype_l(key->l));
        }
    }

}

int CheckVertexCover() {
    hset_traverse(key, T) {
        int CurrentVertex = (int) key->l;
        struct gsllist *CurrentAdjList = AdjLists[CurrentVertex];
        gsl_traverse(cur, CurrentAdjList) {
            int AdjNode = (int) cur->l;
            if (hset_index_of(T, gtype_l(AdjNode)) != -1) {
                return 0;
            }
        }
    }
    return 1;
}

void Output() {
    int isVertexCover = CheckVertexCover();

    if(isVertexCover){
        printf("%s\n", "Là tập đỉnh bao phủ");
    } else {
        printf("%s\n", "Không là tập đỉnh bao phủ");
    }
}

int main(int argc, char *argv[]) {
    Parse_Input(argv[1], argv[2]);
    CreateT();
    Output();

    for (int i = 0; i < N; i++) {
        gsl_free(AdjLists[i]);
    }
    free(AdjLists);
    hset_free(Vertices);
    hset_free(VertexCover);
    hset_free(T);
    return 0;
}