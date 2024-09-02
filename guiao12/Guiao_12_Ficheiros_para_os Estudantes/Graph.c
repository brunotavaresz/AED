//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// Graph - Using a list of adjacency lists representation
//


#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma aresta em um grafo ponderado
struct _Edge {
  unsigned int adjVertex;  // Vértice adjacente
  double weight;           // Peso da aresta
};

// Estrutura para representar um vértice em um grafo
struct _Vertex {
  unsigned int id;         // Identificador do vértice
  unsigned int inDegree;   // Grau de entrada
  unsigned int outDegree;  // Grau de saída
  List* edgesList;         // Lista de arestas
};
    List* edgesList;         // Lista de arestas
};

// Estrutura para representar o cabeçalho de um grafo
struct _GraphHeader {
    int isDigraph;           // 1 se o grafo é direcionado, 0 se não é
    int isComplete;          // 1 se o grafo é completo, 0 se não é
    int isWeighted;          // 1 se o grafo é ponderado, 0 se não é
    unsigned int numVertices; // Número de vértices no grafo
    unsigned int numEdges;    // Número de arestas no grafo
    List* verticesList;       // Lista de vértices
};

// Função auxiliar para adicionar uma aresta
static int _addEdge(Graph* g, unsigned int v, unsigned int w, double weight) {
    struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
    if (edge == NULL) {
        return 0;  // Erro na alocação de memória
    }

    edge->adjVertex = w;
    edge->weight = weight;

    ListMove(g->verticesList, v);
    struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
    int result = ListInsert(vertex->edgesList, edge);

    if (result == -1) {
        free(edge);
        return 0;  // Erro na inserção na lista de adjacências
    } else {
        g->numEdges++;
        vertex->outDegree++;

        ListMove(g->verticesList, w);
        struct _Vertex* destVertex = ListGetCurrentItem(g->verticesList);
        result = ListInsert(destVertex->edgesList, edge);

        if (result == -1) {
            ListRemoveCurrent(vertex->edgesList);
            free(edge);
            return 0;  // Erro na inserção na lista de adjacências do destino
        } else {
            vertex->inDegree++;
            destVertex->outDegree++;
        }
    }

    return 1;  // Aresta adicionada com sucesso
}

// The comparator for the VERTICES LIST

int graphVerticesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Vertex*)p1)->id;
  unsigned int v2 = ((struct _Vertex*)p2)->id;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// The comparator for the EDGES LISTS

int graphEdgesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Edge*)p1)->adjVertex;
  unsigned int v2 = ((struct _Edge*)p2)->adjVertex;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// Função para criar um grafo
Graph* GraphCreate(unsigned int numVertices, int isDigraph, int isWeighted) {
    Graph* g = (Graph*)malloc(sizeof(struct _GraphHeader));
    if (g == NULL) {
        return NULL;  // Erro na alocação de memória
    }

    g->isDigraph = isDigraph;
    g->isComplete = 0;
    g->isWeighted = isWeighted;
    g->numVertices = numVertices;
    g->numEdges = 0;

    g->verticesList = ListCreate(graphVerticesComparator);
    if (g->verticesList == NULL) {
        free(g);
        return NULL;  // Erro na criação da lista de vértices
    }

    for (unsigned int i = 0; i < numVertices; i++) {
        struct _Vertex* v = (struct _Vertex*)malloc(sizeof(struct _Vertex));
        if (v == NULL) {
            // Trate o erro de alocação de memória, se necessário
            GraphDestroy(&g);
            return NULL;
        }

        v->id = i;
        v->inDegree = 0;
        v->outDegree = 0;

        v->edgesList = ListCreate(graphEdgesComparator);
        if (v->edgesList == NULL) {
            // Trate o erro de criação da lista de adjacências, se necessário
            free(v);
            GraphDestroy(&g);
            return NULL;
        }

        ListInsert(g->verticesList, v);
    }

    assert(g->numVertices == ListGetSize(g->verticesList));

    return g;
}

Graph* GraphCreateComplete(unsigned int numVertices, int isDigraph) {
  Graph* g = GraphCreate(numVertices, isDigraph, 0);

  g->isComplete = 1;

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    struct _Vertex* v = ListGetCurrentItem(vertices);
    List* edges = v->edgesList;
    for (unsigned int j = 0; j < g->numVertices; j++) {
      if (i == j) {
        continue;
      }
      struct _Edge* new = (struct _Edge*)malloc(sizeof(struct _Edge));
      if (new == NULL) abort();
      new->adjVertex = j;
      new->weight = 1;

      ListInsert(edges, new);
    }
    if (g->isDigraph) {
      v->inDegree = g->numVertices - 1;
      v->outDegree = g->numVertices - 1;
    } else {
      v->outDegree = g->numVertices - 1;
    }
  }
  if (g->isDigraph) {
    g->numEdges = numVertices * (numVertices - 1);
  } else {
    g->numEdges = numVertices * (numVertices - 1) / 2;
  }

  return g;
}

void GraphDestroy(Graph** p) {
  assert(*p != NULL);
  Graph* g = *p;

  List* vertices = g->verticesList;
  if (ListIsEmpty(vertices) == 0) {
    ListMoveToHead(vertices);
    unsigned int i = 0;
    for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
      struct _Vertex* v = ListGetCurrentItem(vertices);

      List* edges = v->edgesList;
      if (ListIsEmpty(edges) == 0) {
        unsigned int i = 0;
        ListMoveToHead(edges);
        for (; i < ListGetSize(edges); ListMoveToNext(edges), i++) {
          struct _Edge* e = ListGetCurrentItem(edges);
          free(e);
        }
      }
      ListDestroy(&(v->edgesList));
      free(v);
    }
  }

  ListDestroy(&(g->verticesList));
  free(g);

  *p = NULL;
}

static int _addEdge(Graph* g, unsigned int v, unsigned int w, double weight) {
  struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
  edge->adjVertex = w;
  edge->weight = weight;

  ListMove(g->verticesList, v);
  struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
  int result = ListInsert(vertex->edgesList, edge);

  if (result == -1) {
    return 0;
  } else {
    g->numEdges++;
    vertex->outDegree++;

    ListMove(g->verticesList, w);
    struct _Vertex* destVertex = ListGetCurrentItem(g->verticesList);
    destVertex->inDegree++;
  }

  if (g->isDigraph == 0) {
    // Bidirectional edge
    struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
    edge->adjVertex = v;
    edge->weight = weight;

    ListMove(g->verticesList, w);
    struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
    result = ListInsert(vertex->edgesList, edge);

    if (result == -1) {
      return 0;
    } else {
      // g->numEdges++; // Do not count the same edge twice on an undirected
      // graph !!
      vertex->outDegree++;
    }
  }

  return 1;
}

int GraphAddEdge(Graph* g, unsigned int v, unsigned int w) {
  assert(g->isWeighted == 0);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, 1.0);
}

int GraphAddWeightedEdge(Graph* g, unsigned int v, unsigned int w,
                         double weight) {
  assert(g->isWeighted == 1);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, weight);
}

struct _Edge* findEdge(List* edges, unsigned int w) {
  ListMoveToHead(edges);
  while (ListGetCurrentPosition(edges) != ListGetSize(edges)) {
    struct _Edge* e = ListGetCurrentItem(edges);
    if (e->adjVertex == w) {
      return e;
    }
    ListMoveToNext(edges);
  }
  return NULL;
}

int GraphRemoveEdge(Graph* g, unsigned int v, unsigned int w) {
  assert(g != NULL);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);

  List* edges = vertex->edgesList;
  struct _Edge* edgeToRemove = findEdge(edges, w);

  if (edgeToRemove != NULL) {
    ListRemoveCurrent(edges);
    free(edgeToRemove);

    if (g->isDigraph == 0) {
      // For undirected graphs, remove the reverse edge as well
      ListMove(g->verticesList, w);
      struct _Vertex* destVertex = ListGetCurrentItem(g->verticesList);

      List* destEdges = destVertex->edgesList;
      struct _Edge* reverseEdgeToRemove = findEdge(destEdges, v);

      if (reverseEdgeToRemove != NULL) {
        ListRemoveCurrent(destEdges);
        free(reverseEdgeToRemove);
      }
    }

    vertex->outDegree--;
    if (g->isDigraph == 0) {
      ListMove(g->verticesList, w);
      struct _Vertex* destVertex = ListGetCurrentItem(g->verticesList);
      destVertex->inDegree--;
    }

    g->numEdges--;

    return 1;
  }

  return 0;
}

Graph* GraphCopy(const Graph* g) {
  assert(g != NULL);

  Graph* copy = GraphCreate(g->numVertices, g->isDigraph, g->isWeighted);

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  while (ListGetCurrentPosition(vertices) != ListGetSize(vertices)) {
    struct _Vertex* originalVertex = ListGetCurrentItem(vertices);

    List* edges = originalVertex->edgesList;
    ListMoveToHead(edges);
    while (ListGetCurrentPosition(edges) != ListGetSize(edges)) {
      struct _Edge* originalEdge = ListGetCurrentItem(edges);
      GraphAddWeightedEdge(copy, originalVertex->id, originalEdge->adjVertex, originalEdge->weight);
      ListMoveToNext(edges);
    }

    ListMoveToNext(vertices);
  }

  return copy;
}

Graph* GraphFromFile(FILE* f) {
  assert(f != NULL);

  // Assuming the file format is as follows:
  // numVertices numEdges
  // v1 w1 [weight1]
  // v2 w2 [weight2]
  // ...

  unsigned int numVertices, numEdges;
  fscanf(f, "%u %u", &numVertices, &numEdges);

  Graph* g = GraphCreate(numVertices, 0, 0); // Assume undirected and unweighted

  for (unsigned int i = 0; i < numEdges; i++) {
    unsigned int v, w;
    double weight = 1.0;
    fscanf(f, "%u %u", &v, &w);

    if (GraphIsWeighted(g)) {
      fscanf(f, "%lf", &weight);
    }

    GraphAddWeightedEdge(g, v, w, weight);
  }

  return g;
}

void GraphDisplay(const Graph* g) {
    // Implementação para exibir informações sobre o grafo
    printf("Graph Display:\n");

    // Aqui você pode adicionar o código para exibir detalhes do grafo, se necessário
}
