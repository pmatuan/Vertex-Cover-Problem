#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "cgen/all.h"

const int N = 2e6;
struct gsllist **AdjLists;
struct hset *Vertices;

int NumberOfNodes, NumberOfEdges;

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
}

void BFS(struct gsllist **AdjLists, int startVertex, bool visited[]){
    struct gsllist *queue = gsl_create_list(NULL);

    visited[startVertex] = true;
    gsl_push_back(queue, gtype_l(startVertex));

    while (!gsl_is_empty(queue)) {
        int currentVertex = gsl_front_value(queue)->l;
        gsl_pop_front(queue);
        printf("Visited %d\n", currentVertex);

        gsl_traverse(cur, AdjLists[currentVertex]) {
            if (!visited[cur->l]) {
                visited[cur->l] = true;
                gsl_push_back(queue, gtype_l(cur->l));
            }
        }
    }
    gsl_free(queue);
}

void DFS(struct gsllist **AdjLists, int startVertex, bool visited[]){
    struct gsllist *queue = gsl_create_list(NULL);

    visited[startVertex] = true;
    printf("Visited %d\n", startVertex);

    gsl_traverse(cur, AdjLists[startVertex]) {
        if (!visited[cur->l]) {
            DFS(AdjLists, cur->l, visited);
        }
    }
    gsl_free(queue);
}

int main(int argc, char *argv[]) {
    Parse_Input(argv[1], argv[2]);
    bool visited[N];
    memset(&visited, false, sizeof(visited));

    printf("Breadth-first Search starting from vertex 1\n");
    BFS(AdjLists, 1, visited);
    memset(&visited, false, sizeof(visited));

    printf("Depth-first Search starting from vertex 3\n");
    DFS(AdjLists, 3, visited);
    memset(&visited, false, sizeof(visited));

    for (int i = 0; i < N; i++) {
        gsl_free(AdjLists[i]);
    }
    free(AdjLists);
    hset_free(Vertices);
    return 0;
}