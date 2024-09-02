//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// GraphBFS - QUEUE-based Breadth-First Search
//

#include "GraphBFSWithQueue.h"
#include "IntegersQueue.h"  // Include the header file for IntegersQueue

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"

struct _GraphBFSWithQueue {
  int* marked;       // To mark vertices when reached for the first time
  int* distance;     // The number of edges on the path from the start vertex
  int* predecessor;  // The predecessor vertex, when a vertex was reached
  Graph* graph;
  unsigned int startVertex;
};

GraphBFSWithQueue* GraphBFSWithQueueExecute(Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));

  GraphBFSWithQueue* traversal =
      (GraphBFSWithQueue*)malloc(sizeof(struct _GraphBFSWithQueue));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  // Initialize marked array
  traversal->marked = (int*)calloc(numVertices, sizeof(int));
  assert(traversal->marked != NULL);

  // Initialize distance array
  traversal->distance = (int*)malloc(numVertices * sizeof(int));
  assert(traversal->distance != NULL);
  for (unsigned int i = 0; i < numVertices; i++) {
    traversal->distance[i] = -1;  // Initialize distances to -1 (not reachable)
  }

  // Initialize predecessor array
  traversal->predecessor = (int*)malloc(numVertices * sizeof(int));
  assert(traversal->predecessor != NULL);
  for (unsigned int i = 0; i < numVertices; i++) {
    traversal->predecessor[i] = -1;  // Initialize predecessors to -1
  }

  traversal->graph = g;
  traversal->startVertex = startVertex;

  // Inicializar a fila
  IntegersQueue* queue = IntegersQueueCreate(numVertices);


  

  // Enqueue the start vertex
  IntegersQueueEnqueue(queue, startVertex);
  traversal->marked[startVertex] = 1;
  traversal->distance[startVertex] = 0;  // Distance to start vertex is 0

  // BFS traversal loop
  while (!IntegersQueueIsEmpty(queue)) {
    unsigned int currentVertex = IntegersQueueDequeue(queue);

    // Traverse the adjacent vertices
    unsigned int* adjacents = GraphGetAdjacentsTo(g, currentVertex);
    for (unsigned int i = 0; i < GraphGetVertexDegree(g, currentVertex); i++) {
      unsigned int adjacentVertex = adjacents[i];
      if (!traversal->marked[adjacentVertex]) {
        traversal->marked[adjacentVertex] = 1;
        traversal->distance[adjacentVertex] = traversal->distance[currentVertex] + 1;
        traversal->predecessor[adjacentVertex] = currentVertex;

        // Enqueue the adjacent vertex
        IntegersQueueEnqueue(queue, adjacentVertex);
      }
    }
  }

  // Clean up the queue
  IntegersQueueDestroy(&queue);

  return traversal;
}

void GraphBFSWithQueueDestroy(GraphBFSWithQueue** p) {
  assert(*p != NULL);

  GraphBFSWithQueue* aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphBFSWithQueueHasPathTo(const GraphBFSWithQueue* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack* GraphBFSWithQueuePathTo(const GraphBFSWithQueue* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBFSWithQueueShowPath(const GraphBFSWithQueue* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBFSWithQueuePathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphBFSWithQueueDisplay(const GraphBFSWithQueue* p) {
  assert(p != NULL);

  printf("BFS Traversal Order (starting from vertex %u): ", p->startVertex);

  unsigned int numVertices = GraphGetNumVertices(p->graph);

  // Display the order in which vertices are visited (BFS order)
  for (unsigned int i = 0; i < numVertices; i++) {
    printf("%u ", i);
  }

  printf("\n");

  // Display distances from the start vertex
  printf("Distances from start vertex %u:\n", p->startVertex);
  for (unsigned int i = 0; i < numVertices; i++) {
    printf("Vertex %u: %d\n", i, p->distance[i]);
  }
}