#include "all.c"

const int N = 2e6;
struct gvector *AdjLists;
struct hset *Vertices;
struct hset *VertexCover;
struct hset *T;
int NumberOfNodes, NumberOfEdges, SizeOfVertexCover;

void parse_input(char *graph, char *vc) {
    FILE *Graph = fopen(graph, "r");
    int source, sink;

    fscanf(Graph, "%d %d\n", &NumberOfNodes, &NumberOfEdges);
    printf("%d %d\n", NumberOfNodes, NumberOfEdges);

    // fscanf(Graph, "%d %d\n", &source, &sink);
    // printf("%d %d\n", source, sink);
    AdjLists = gvec_create(N, gtype_free_gsl);
    Vertices = hset_create(gtype_hash_l, gtype_cmp_l, NULL);

    int iteration = 0;
    for (int i = 0; i < NumberOfEdges; i++) {
        fscanf(Graph, "%d %d\n", &source, &sink);
        // printf("%d %d\n", source, sink);
        // hset_insert(Vertices, gtype_l(source));
        int appeared = !hset_insert(Vertices, gtype_l(source));
        // printf("vertex %d appeared: %d\n", source, appeared);
        if (!appeared) {
            struct gsllist *NewAdjList = gsl_create_list(NULL);
            gvec_force_set(AdjLists, source, gtype_gsl(NewAdjList));
            // gvec_elem(AdjLists, source) = gtype_gsl(gsl_create_list(NULL));
        }
        // gsl_push_back(&gvec_elem(AdjLists, source), gtype_l(sink));
        // iteration++;
        // if (iteration == 3) break;

    }

    printf("Vertices:\n");
    hset_traverse(key, Vertices) {
        printf("%ld\n", key->l);
    }

    
    fclose(Graph);

    FILE *VC = fopen(vc, "r");
    int vertex;

    fscanf(VC, "%d\n", &SizeOfVertexCover);
    // printf("%d\n", SizeOfVertexCover);

    VertexCover = hset_create(gtype_hash_l, gtype_cmp_l, NULL);

    for (int i = 0; i < SizeOfVertexCover; i++) {
        fscanf(VC, "v %d\n", &vertex);
        hset_insert(VertexCover, gtype_l(vertex));
    }
    printf("VertexCover:\n");
    hset_traverse(key, VertexCover) {
        printf("%ld\n", key->l);
    }
    
    fclose(VC);
}

void CreateT(){
    T = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    
    hset_traverse(key, Vertices) {
        if (hset_insert(VertexCover, *key)) {
            hset_insert(T, *key);
        }
    }

    printf("T:\n");
    hset_traverse(key, T) {
        printf("%ld\n", key->l);
    }
}

int CheckVertexCover() {
    hset_traverse(key, T) {
        int CurrentVertex = key->l;
        struct gsllist *CurrentAdjList;
        gvec_elem(AdjLists, CurrentVertex) = gtype_gsl(CurrentAdjList);
        gsl_traverse(cur, CurrentAdjList) {
            int AdjNode = cur->l;
            int exited = !hset_insert(T, gtype_l(AdjNode));
            if (exited) return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    parse_input(argv[1], argv[2]);
    CreateT();
    printf("Already run\n");

    // gvec_free(AdjLists);
    hset_free(Vertices);
    hset_free(VertexCover);
    hset_free(T);
    return 0;
}