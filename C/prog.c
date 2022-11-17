#include "all.c"

const int N = 2e6;
struct gsllist **AdjLists;
struct hset *Vertices, *VertexCover, *T;
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


    T = hset_create(gtype_hash_l, gtype_cmp_l, NULL);
    
    hset_traverse(key, Vertices) {
        if (hset_index_of(VertexCover, gtype_l(key->l)) == -1) {
            hset_insert(T, gtype_l(key->l));
        }
    }
}


void BFS(int startVertex, bool visited[]){
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

void DFS(int startVertex, bool visited[]){
    visited[startVertex] = true;
    printf("Visited %d\n", startVertex);
    gsl_traverse(cur, AdjLists[startVertex]) {
        if (!visited[cur->l]) {
            DFS(cur->l, visited);
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

void Free(){
    for (int i = 0; i < N; i++) {
        gsl_free(AdjLists[i]);
    }
    free(AdjLists);
    hset_free(Vertices);
    hset_free(VertexCover);
    hset_free(T);
}

void menu(){
    printf("Chương trình thực hiện các thao tác trên đồ thị\n");
    printf("Chọn thao tác bạn muốn thực hiện\n");
    printf("1. Duyệt đồ thị theo thuật toán BFS\n");
    printf("2. Duyệt đồ thị theo thuật toán DFS\n");
    printf("3. Kiểm tra tập đỉnh bao phủ\n");
    printf("4. Thoát\n");
    printf("Lựa chọn của bạn là [1-4]: ");
}

int main(int argc, char *argv[]) {
    bool visited[N];
    Parse_Input(argv[1], argv[2]);
    int choice = -1;
    do{
        menu();
        scanf("%d",&choice);
        if(choice == 1){
            memset(&visited, false, sizeof(visited));
            int startVertex;
            printf("Nhập đỉnh bắt đầu: ");
            scanf("%d", &startVertex);
            BFS(startVertex, visited);
        }
        else if(choice == 2){
            memset(&visited, false, sizeof(visited));
            int startVertex;
            printf("Nhập đỉnh bắt đầu: ");
            scanf("%d", &startVertex);
            DFS(startVertex, visited);
        }
        else if(choice == 3){
            int isVertexCover = CheckVertexCover();
            if(isVertexCover){
                printf("%s\n", "Là tập đỉnh bao phủ");
            } else {
                printf("%s\n", "Không là tập đỉnh bao phủ");
            }
        }
    }while(choice != 4);

    Free();
    return 0;
}