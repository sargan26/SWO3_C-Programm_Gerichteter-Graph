#include <stdio.h>
#include <stdlib.h>
#include "directed_graph.h"

int main () {
   // -- Testen des Moduls Directed Graph --
   printf("-- Testen des Moduls Directed Graph --\n");
   graph *graph1 = createGraph();
   insertNode(graph1, "A", "Hello from A");
   insertNode(graph1, "B", "Hello from B");
   insertNode(graph1, "C", "Hello from C");
   insertNode(graph1, "D", "Hello from D");
   insertNode(graph1, "E", "Hello from E");

   insertEdge(graph1, "A", "B");
   insertEdge(graph1, "A", "C");
   insertEdge(graph1, "A", "D");
   insertEdge(graph1, "A", "E");

   insertEdge(graph1, "B", "D");

   insertEdge(graph1, "C", "B");
   insertEdge(graph1, "C", "E");

   printGraph(graph1);
   destroyGraph(graph1);

   printf("\n");
   graph *graph2 = createGraph();
   insertNode(graph2, "A", "Hello from A");
   insertNode(graph2, "B", "Hello from B");
   insertNode(graph2, "C", "Hello from C");
   insertNode(graph2, "D", "Hello from D");
   insertNode(graph2, "E", "Hello from E");

   insertEdge(graph2, "A", "B");
   insertEdge(graph2, "A", "D");
   insertEdge(graph2, "A", "E");

   insertEdge(graph2, "B", "C");

   insertEdge(graph2, "C", "D");

   insertEdge(graph2, "D", "A");

   printGraph(graph2);
   destroyGraph(graph2);

   printf("\n");
   graph *graph3 = createGraph();

   printGraph(graph3);
   destroyGraph(graph3);

   printf("\n");
   graph *graph4 = createGraph();

   insertNode(graph4, "A", "Hello from A");
   insertNode(graph4, "A", "Hello from A");
   insertNode(graph4, "B", "Hello from B");

   insertEdge(graph4, "A", "B");
   insertEdge(graph4, "A", "B");
   insertEdge(graph4, "B", "A");
   insertEdge(graph4, "C", "A");
   insertEdge(graph4, "A", "C");

   printGraph(graph4);
   destroyGraph(graph4);

   printf("\n");
   graph *graph5 = createGraph();
   insertNode(graph5, "A", "Hello from A");
   insertNode(graph5, "B", "Hello from B");
   insertNode(graph5, "C", "Hello from C");
   insertNode(graph5, "D", "Hello from D");
   insertNode(graph5, "E", "Hello from E");

   insertEdge(graph5, "A", "B");
   insertEdge(graph5, "A", "C");
   insertEdge(graph5, "A", "D");
   insertEdge(graph5, "A", "E");

   insertEdge(graph5, "B", "D");

   insertEdge(graph5, "C", "B");
   insertEdge(graph5, "C", "E");

   printf("Vor löschen:\n");
   printGraph(graph5);
   deleteEdge(graph5, "C", "E");
   deleteNode(graph5, "A");
   deleteNode(graph5, "F");
   printf("Nach löschen:\n");
   printGraph(graph5);
   destroyGraph(graph5);

   return 0;
}
