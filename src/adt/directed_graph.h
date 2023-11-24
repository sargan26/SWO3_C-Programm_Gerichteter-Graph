#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

// Struktur für Kanten
typedef struct adjacencyNode {
    char *to;
    struct adjacencyNode *next;
} adjacencyNode;

// Struktur für KantenListe
typedef struct adjacencyList {
    adjacencyNode *head;
} adjacencyList;

// Struktur für Knoten
typedef struct node
{
    char *key; // Eindeutige ID für Knoten
    char *message;
    struct adjacencyList *head;
    struct node *next;
} node;

// Struktur für Graph
typedef struct graph
{
    node *head;
} graph;

graph *createGraph();
void destroyGraph(graph *graph);

void insertNode(graph *graph, char *key, char *message);
void deleteNode(graph *graph, char *key);

void insertEdge(graph *graph, char *from, char *to);
void deleteEdge(graph *graph, char *from, char *to);

void printGraph(graph *graph);

#endif