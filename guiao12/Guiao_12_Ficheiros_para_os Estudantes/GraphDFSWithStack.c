//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// GraphDFS - STACK-based Depth-First Search
//

#include "GraphDFSWithStack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"

struct _GraphDFSWithStack {
  int* marked;       // To mark vertices when reached for the first time
  int* predecessor;  // The predecessor vertex, when a vertex was reached
  Graph* graph;
  unsigned int startVertex;
};

void performDFSWithStack(GraphDFSWithStack* traversal) {
  // Create a stack to keep track of vertices to visit
  Stack* stack = StackCreate(GraphGetNumVertices(traversal->graph));
  
  // Push the start vertex onto the stack
  StackPush(stack, traversal->startVertex);
  
  // Mark the start vertex as visited
  traversal->marked[traversal->startVertex] = 1;

  while (!StackIsEmpty(stack)) {
    // Pop a vertex from the stack
    unsigned int currentVertex = StackPop(stack);

    // Process the current vertex (you can perform any required actions here)

    // Traverse the adjacent vertices
    for (unsigned int i = 0; i < GraphGetNumVertices(traversal->graph); i++) {
      if (GraphIsAdjacent(traversal->graph, currentVertex, i) &&
          !traversal->marked[i]) {
        // Mark the vertex as visited and update predecessor
        traversal->marked[i] = 1;
        traversal->predecessor[i] = currentVertex;
        
        // Push the adjacent vertex onto the stack
        StackPush(stack, i);
      }
    }
  }

  // Clean up the stack
  StackDestroy(&stack);
}

GraphDFSWithStack* GraphDFSWithStackExecute(Graph* g,
                                            unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));

  GraphDFSWithStack* traversal =
      (GraphDFSWithStack*)malloc(sizeof(struct _GraphDFSWithStack));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  traversal->marked = (int*)calloc(numVertices, sizeof(unsigned int));
  assert(traversal->marked != NULL);

  traversal->predecessor = (int*)malloc(numVertices * sizeof(int));
  assert(traversal->predecessor != NULL);
  for (unsigned int i = 0; i < numVertices; i++) {
    traversal->predecessor[i] = -1;
  }

  traversal->predecessor[startVertex] = 0;

  traversal->graph = g;
  traversal->startVertex = startVertex;

  // Perform DFS traversal
  performDFSWithStack(traversal);

  return traversal;
}


void GraphDFSWithStackDestroy(GraphDFSWithStack** p) {
  assert(*p != NULL);

  GraphDFSWithStack* aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphDFSWithStackHasPathTo(const GraphDFSWithStack* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack* GraphDFSWithStackPathTo(const GraphDFSWithStack* p, unsigned int v) {
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

void GraphDFSWithStackShowPath(const GraphDFSWithStack* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphDFSWithStackPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphDFSWithStackDisplay(const GraphDFSWithStack* p) {
  assert(p != NULL);

  printf("DFS Traversal Order (starting from vertex %u): ", p->startVertex);

  // Initialize a stack for displaying the traversal order
  Stack* displayStack = StackCreate(GraphGetNumVertices(p->graph));

  // Initialize an array to track whether a vertex has been printed
  int* printed = (int*)calloc(GraphGetNumVertices(p->graph), sizeof(int));

  // Push the start vertex onto the display stack
  StackPush(displayStack, p->startVertex);
  printed[p->startVertex] = 1;

  while (!StackIsEmpty(displayStack)) {
    unsigned int currentVertex = StackPop(displayStack);
    printf("%u ", currentVertex);

    // Push adjacent vertices onto the stack (if not already printed)
    for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
      if (GraphIsAdjacent(p->graph, currentVertex, i) && !printed[i]) {
        StackPush(displayStack, i);
        printed[i] = 1;
      }
    }
  }

  printf("\n");

  // Clean up
  StackDestroy(&displayStack);
  free(printed);
}

