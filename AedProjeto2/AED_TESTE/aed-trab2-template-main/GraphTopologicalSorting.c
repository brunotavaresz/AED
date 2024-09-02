//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"
#include "SortedList.h"

struct _GraphTopoSort {
  int* marked;                     // Aux array
  unsigned int* numIncomingEdges;  // Aux array
  unsigned int* vertexSequence;    // The result
  int validResult;                 // 0 or 1
  unsigned int numVertices;        // From the graph
  Graph* graph;
};

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
static GraphTopoSort* _create(Graph* g) {
  assert(g != NULL);

  GraphTopoSort* p = NULL;

  // TO BE COMPLETED
  // ...

  // Allocate memory for the struct
  p = (GraphTopoSort*)malloc(sizeof(GraphTopoSort));
  if (p == NULL) {
    printf("Error in _create(): memory allocation failed!\n");
    exit(0);
  }

  // Initialize all struct fields
  p->graph = g;
  p->numVertices = GraphGetNumVertices(g);
  p->validResult = 0;

  // Allocate memory for the array fields
  p->marked = (int*)calloc(p->numVertices, sizeof(int));
  if (p->marked == NULL) {
    printf("Error in _create(): memory allocation failed!\n");
    exit(0);
  }

  p->numIncomingEdges = (unsigned int*)calloc(p->numVertices, sizeof(int));
  if (p->numIncomingEdges == NULL) {
    printf("Error in _create(): memory allocation failed!\n");
    exit(0);
  }

  p->vertexSequence = (unsigned int*)calloc(p->numVertices, sizeof(int));
  if (p->vertexSequence == NULL) {
    printf("Error in _create(): memory allocation failed!\n");
    exit(0);
  }

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct
  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting
  Graph* copy = GraphCopy(g); // Cria uma cópia do grafo original

  while (topoSort->numVertices > 0) {
    int v = -1; // Variável para armazenar o vértice sem arestas incidentes

    // Percorre todos os vértices para encontrar um vértice sem arestas incidentes
    for (unsigned int i = 0; i < GraphGetNumVertices(copy); i++) {
      if (topoSort->marked[i] == 0 && GraphGetVertexInDegree(copy, i) == 0) {
        v = i;
        break;
      }
    }

    if (v == -1) {
      break; // Se nenhum vértice sem arestas incidentes for encontrado, o grafo contém um ciclo
    }

    topoSort->marked[v] = 1; // Marca o vértice como visitado

    unsigned int* adjVertices = GraphGetAdjacentsTo(copy, v); // Obtém os vértices adjacentes ao vértice v
    for (unsigned int i = 0; i < GraphGetVertexOutDegree(copy, v); i++) {
      unsigned int adjVertex = adjVertices[i];
      topoSort->numIncomingEdges[adjVertex]--;
    }

    GraphRemoveEdge(copy, v, v); // Remove as arestas incidentes do vértice v
    topoSort->vertexSequence[topoSort->numVertices - 1] = v; // Adiciona o vértice na sequência
    topoSort->numVertices--;
  }

  // Verifica se a ordenação topológica é válida
  if (topoSort->numVertices == 0) {
    topoSort->validResult = 1;
  }

  // Libera a memória alocada para a cópia do grafo
  GraphDestroy(&copy);

  return topoSort;
}


//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV2(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // Build the topological sorting
  // 2º algoritmo - Array auxiliar
  // Registra em numEdgesPerVertex o InDegree de cada vértice
  unsigned int* numEdgesPerVertex = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
  assert(numEdgesPerVertex != NULL);

  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
    numEdgesPerVertex[i] = GraphGetVertexInDegree(g, i);
  }

  // Enquanto houver vértices com InDegree 0, adicioná-los à sequência
  unsigned int index = 0;
   while (index < GraphGetNumVertices(g)) {
    // Seleciona vértice v com numEdgesPerVertex[v] == 0 e não marcado
    unsigned int v = 0;
    while (v < GraphGetNumVertices(g) && (numEdgesPerVertex[v] != 0 || topoSort->marked[v] == 1)) {
      v++;
    }

    if (v == GraphGetNumVertices(g)) {
      // Não foi possível encontrar um vértice válido, há um ciclo no grafo
      break;
    }

    // Imprime o ID do vértice
    topoSort->vertexSequence[index++] = v;

    // Marca o vértice como pertencendo à ordenação
    topoSort->marked[v] = 1;

    // Para cada vértice w adjacente a v
    unsigned int* adjacents = GraphGetAdjacentsTo(g, v);
    unsigned int numAdjacents = GraphGetVertexOutDegree(g, v);

    for (unsigned int j = 0; j < numAdjacents; j++) {
      unsigned int w = adjacents[j];
      numEdgesPerVertex[w]--;
    }
  }

  // Verifica se uma ordenação válida foi calculada
  topoSort->validResult = (index == GraphGetNumVertices(g));

  // Libera a memória do array auxiliar
  free(numEdgesPerVertex);

  // Retorna a estrutura resultante da ordenação topológica
  return topoSort;

}

//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Create and initialize the struct

  GraphTopoSort* topoSort = _create(g);

  // 3º algoritmo - Manter o conjunto de candidatos
  // Registra em numEdgesPerVertex o InDegree de cada vértice
  unsigned int* numEdgesPerVertex = (unsigned int*)malloc(GraphGetNumVertices(g) * sizeof(unsigned int));
  assert(numEdgesPerVertex != NULL);

  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
    numEdgesPerVertex[i] = GraphGetVertexInDegree(g, i);
  }

// Cria uma FILA vazia e insere nela os vértices v com numEdgesPerVertex[v] == 0
  Queue* queue = QueueCreate(GraphGetNumVertices(g)); 

  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
    if (numEdgesPerVertex[i] == 0) {
      QueueEnqueue(queue, i);
    }
  }

  // Enquanto a FILA não for vazia
  unsigned int index = 0;
  while (!QueueIsEmpty(queue)) {
    // Retira o próximo vértice da FILA
    unsigned int v = QueueDequeue(queue);

    // Imprime o ID do vértice
    topoSort->vertexSequence[index++] = v;

    // Para cada vértice w adjacente a v
    unsigned int* adjacents = GraphGetAdjacentsTo(g, v);
    unsigned int numAdjacents = GraphGetVertexOutDegree(g, v);

    for (unsigned int j = 0; j < numAdjacents; j++) {
      unsigned int w = adjacents[j];
      numEdgesPerVertex[w]--;

      // Se numEdgesPerVertex[w] == 0, insere w na FILA
      if (numEdgesPerVertex[w] == 0) {
        QueueEnqueue(queue, w);
      }
    }
  }

  // Verifica se uma ordenação válida foi calculada
  topoSort->validResult = (index == GraphGetNumVertices(g));

  // Libera a memória dos arrays auxiliares
  free(numEdgesPerVertex);
  QueueDestroy(&queue);

  // Retorna a estrutura resultante da ordenação topológica
  return topoSort;
}

void GraphTopoSortDestroy(GraphTopoSort** p) {
  assert(*p != NULL);

  GraphTopoSort* aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort* p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
unsigned int* GraphTopoSortGetSequence(const GraphTopoSort* p) {
  assert(p != NULL);
  // TO BE COMPLETED
  // ...

  if (p->validResult == 1) {
    unsigned int* sequence = (unsigned int*)malloc(p->numVertices * sizeof(unsigned int));
    assert(sequence != NULL);

    for (unsigned int i = 0; i < p->numVertices; i++) {
      sequence[i] = p->vertexSequence[i];
    }

    return sequence;
  }
  
  return NULL;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort* p) {
  assert(p != NULL);

  if (p->validResult == 0) {
    printf(" *** The topological sorting could not be computed!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort* p) {
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0) {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}