#include <stdio.h>
#include <stdlib.h>

// Structura pentru nodul din lista de adiacența
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Creeaza un nod nou
Node* create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

// Creeaza un graf cu un numar dat de varfuri
Graph* create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Adauga o muchie intre doua noduri
void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Introduce muchii în graf
void insert_edges(int edge_count, Graph *graph) {
    int src, dest;
    printf("Adauga %d muchii (perechi de noduri):\n", edge_count);
    for (int i = 0; i < edge_count; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Verifică dacă coada este goală
int is_empty(Node *queue) {
    return queue == NULL;
}

// Adauga in coada
void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Scoate din coada
int dequeue(Node **queue) {
    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

// Reseteaza lista visited
void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Parcurgere DFS
void DFS(Graph *graph, int vertex) {
    Node *temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Parcurgere BFS
void BFS(Graph *graph, int start) {
    Node *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nr_of_vertices;
    int nr_of_edges;
    int starting_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);

    Graph *graph = create_graph(nr_of_vertices);
    insert_edges(nr_of_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    reset_visited(graph);

    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");

    return 0;
}
