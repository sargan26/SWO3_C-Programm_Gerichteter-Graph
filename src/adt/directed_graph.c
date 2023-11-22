#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directed_graph.h"

// Funktion zum Erstellen einer neuen verketteten Liste
graph *createGraph() {
    graph *list = malloc(sizeof(graph));
    if (list == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

// Funktion zum Erstellen einer neuen verketteten Liste für Kanten
adjacencyList *createAdjacencyList() {
    adjacencyList *list = malloc(sizeof(adjacencyList));
    if (list == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

// Funktion zum Zerstören der verketteten Liste der Kanten und aller zugehörigen Ressourcen
void destroyAdjacencyList(adjacencyList *list) {
    adjacencyNode *current = list->head;
    while (current != NULL) {
        adjacencyNode *next = current->next;
        free(current->to);
        free(current);
        current = next;
    }
}

// Funktion zum Zerstören der verketteten Liste und aller zugehörigen Ressourcen
void destroyGraph(graph *graph) {
    node *current = graph->head;
    while (current != NULL) {
        node *next = current->next;
        free(current->key);
        free(current->message);
        destroyAdjacencyList(current->head);
        free(current);
        current = next;
    }
    free(graph);
}

// Funktion zum Überprüfen, ob ein Schlüssel bereits in der Liste vorhanden ist
int keyExists(graph *graph, char *key) {
    node *current = graph->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

// Funktion zum Überprüfen, ob ein Schlüssel bereits in der Liste vorhanden ist
int keyExistsAdjacency(adjacencyList *list, char *key) {
    adjacencyNode *current = list->head;
    while (current != NULL) {
        if (strcmp(current->to, key) == 0) {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
}

// Funktion zum Einfügen eines Knotens
void insertNode(graph *graph, char *key, char *message) {
    // Überprüfen, ob der Schlüssel bereits vorhanden ist
    if (keyExists(graph, key)) {
        printf("Knoten '%s' bereits vorhanden. Der Knoten wird nicht eingefügt.\n", key);
        return;
    }

    // Allokation für den neuen Knoten
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        exit(EXIT_FAILURE);
    }

    // Allokation für die Zeichenketten 'key' und 'message'
    newNode->key = malloc(strlen(key) + 1);
    newNode->message = malloc(strlen(message) + 1);
    if (newNode->key == NULL || newNode->message == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        free(newNode->key);
        free(newNode->message);
        free(newNode);
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->key, key);
    strcpy(newNode->message, message);
    newNode->head = createAdjacencyList();

    // Spezialfall: Leere Liste oder neuer Knoten vor dem ersten Knoten einfügen
    if (graph->head == NULL || strcmp(newNode->key, graph->head->key) < 0) {
        newNode->next = graph->head;
        graph->head = newNode;
    } else {
        // Finden Sie die richtige Position für den neuen Knoten in der sortierten Liste
        node *current = graph->head;
        while (current->next != NULL && strcmp(newNode->key, current->next->key) >= 0) {
            current = current->next;
        }

        // Fügen Sie den neuen Knoten an der gefundenen Position ein
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Prozedur zum Löschen eines Knotens und aller inzidenten Kanten
void deleteNode(graph *graph, char *key) {
    // Finden des Knotens
    node *currentNode = graph->head;
    node *prevNode = NULL;

    while (currentNode != NULL && strcmp(currentNode->key, key) != 0) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // currentNode sollte nun den zu löschenden Knoten oder NULL referenzieren
    if (currentNode != NULL) {
        // Entfernen des Knotens aus der Liste
        if (prevNode != NULL) {
            prevNode->next = currentNode->next;
        } else {
            graph->head = currentNode->next;
        }

        // Löschen aller inzidenten Kanten
        destroyAdjacencyList(currentNode->head);

        // Freigabe der Ressourcen des zu löschenden Knotens
        free(currentNode->key);
        free(currentNode->message);
        free(currentNode);
    } else {
        // Fehler: Der zu löschende Knoten wurde nicht gefunden
        printf("Fehler: Knoten '%s' nicht im Graphen gefunden.\n", key);
    }
}

// Funktion zum Einfügen eines Knotens in die Liste der Knoten
void insertAdjacencyNode(adjacencyList *list, char *key) {
    // Überprüfen, ob der Schlüssel bereits vorhanden ist
    if (keyExistsAdjacency(list, key)) {
        printf("Verbindung zu '%s' bereits vorhanden. Die Kante wird nicht eingefügt.\n", key);
        return;
    }
    // Allokation für den neuen Knoten
    adjacencyNode *newNode = malloc(sizeof(adjacencyNode));
    if (newNode == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        exit(EXIT_FAILURE);
    }

    // Allokation für die Zeichenkette 'key'
    newNode->to = malloc(strlen(key) + 1);
    if (newNode->to == NULL) {
        // Fehlerbehandlung bei Allokationsfehler
        free(newNode);
        exit(EXIT_FAILURE);
    }

    strcpy(newNode->to, key);
    newNode->next = NULL;

    // Spezialfall: Leere Liste oder neuer Knoten vor dem ersten Knoten einfügen
    if (list->head == NULL || strcmp(newNode->to, list->head->to) < 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        // Finden Sie die richtige Position für den neuen Knoten in der sortierten Liste
        adjacencyNode *current = list->head;
        while (current->next != NULL && strcmp(newNode->to, current->to) >= 0) {
            current = current->next;
        }

        // Fügen Sie den neuen Knoten an der gefundenen Position ein
        newNode->next = current->next;
        current->next = newNode;
    }
}


// Prozedur zum Einfügen einer Kante in den Graphen
void insertEdge(graph *graph, char *from, char *to) {
    // Überprüfen, ob der Startknoten "from" vorhanden ist, andernfalls einfügen
    if (!keyExists(graph, from)) {
        printf("Fehler: Startknoten '%s' nicht im Graphen gefunden.\n", from);
        return;
    }
    // Überprüfen, ob der Endknoten "to" vorhanden ist, andernfalls einfügen
    if (!keyExists(graph, to)) {
        printf("Fehler: Endknoten '%s' nicht im Graphen gefunden.\n", to);
        return;
    }

    // Finden des Knotens "from"
    node *currentNode = graph->head;
    while (currentNode != NULL && strcmp(currentNode->key, from) != 0) {
        currentNode = currentNode->next;
    }

    // currentNode sollte nun den Knoten "from" referenzieren
    if (currentNode != NULL) {
        // Einfügen des neuen Knotens in die Adjazenzliste für "from"
        insertAdjacencyNode(currentNode->head, to);
    } else {
        // Fehler: Der Knoten "from" wurde nicht gefunden
        printf("Fehler: Startknoten '%s' nicht im Graphen gefunden.\n", from);
    }
}

// Prozedur zum Löschen einer Kante aus dem Graphen
void deleteEdge(graph *graph, char *from, char *to) {
    // Überprüfen, ob der Startknoten "from" vorhanden ist
    if (!keyExists(graph, from)) {
        printf("Fehler: Startknoten '%s' nicht im Graphen gefunden.\n", from);
        return;
    }

    // Finden des Knotens "from"
    node *currentNode = graph->head;
    while (currentNode != NULL && strcmp(currentNode->key, from) != 0) {
        currentNode = currentNode->next;
    }

    // currentNode sollte nun den Knoten "from" referenzieren
    if (currentNode != NULL) {
        // Suchen der Kante "to" in der Adjazenzliste für "from"
        adjacencyNode *currentAdjacency = currentNode->head->head;
        adjacencyNode *prevAdjacency = NULL;

        while (currentAdjacency != NULL && strcmp(currentAdjacency->to, to) != 0) {
            prevAdjacency = currentAdjacency;
            currentAdjacency = currentAdjacency->next;
        }

        // Überprüfen, ob die Kante gefunden wurde
        if (currentAdjacency != NULL) {
            // Kante aus der Liste entfernen
            if (prevAdjacency != NULL) {
                prevAdjacency->next = currentAdjacency->next;
            } else {
                currentNode->head->head = currentAdjacency->next;
            }

            // Freigabe der Ressourcen der Kante
            free(currentAdjacency->to);
            free(currentAdjacency);
        } else {
            // Fehler: Die Kante "to" wurde nicht gefunden
            printf("Fehler: Kante von '%s' zu '%s' nicht im Graphen gefunden.\n", from, to);
        }
    } else {
        // Fehler: Der Knoten "from" wurde nicht gefunden
        printf("Fehler: Startknoten '%s' nicht im Graphen gefunden.\n", from);
    }
}

// Funktion zum Drucken der verketteten Liste
void printGraph(graph *graph) {
    node *current = graph->head;
    printf("Node list:\n");
    while (current != NULL) {
        printf("Node: %s, Payload: %s\n", current->key, current->message);
        current = current->next;
    }

    printf("\n");
    printf("Edges list:\n");
    current = graph->head;
    while (current != NULL) {
        printf("%s: ", current->key);
        adjacencyNode *currentAdjacency = current->head->head;
        int first = 1;
        while (currentAdjacency != NULL) {
            if (first == 1)
            {
                printf("%s", currentAdjacency->to);
                first = 0;
            } else {
                printf(",%s", currentAdjacency->to);
            }
            currentAdjacency = currentAdjacency->next;
        }
        printf("\n");
        current = current->next;
    }

}