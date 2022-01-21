/*************************************************************
 * IST - ASA 21/22
 * Group - al038
 * Diogo Melita, 99202
 * Diogo Gaspar, 99207
 ************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

typedef struct Vertex {
  Vertex *leftParent;
  Vertex *rightParent;
  int parentAmount = 0;
  int id;
} Vertex;

#define MAX_PARENTS 2
using Node = int;
using Color = enum { WHITE, GRAY, BLACK };
using Graph = std::vector<Vertex*>;
using Ancestors = std::vector<Color>;

bool isCyclicVisit(int id, std::vector<Color> &visited, Graph &adjList) {
  visited[id] = GRAY;
  if (adjList[id]->leftParent != nullptr && (visited[adjList[id]->leftParent->id] == GRAY || isCyclicVisit(adjList[id]->leftParent->id, visited, adjList))) {
    return true;
  }
  if (adjList[id]->rightParent != nullptr && (visited[adjList[id]->rightParent->id] == GRAY || isCyclicVisit(adjList[id]->rightParent->id, visited, adjList))) {
    return true;
  }
  visited[id] = BLACK;
  return false;
}

bool isCyclic(int noNodes, Graph &adjList) {
  std::vector<Color> visited(noNodes, WHITE);
  for (Node i = 1; i <= noNodes; i++) {
    if (visited[i] == WHITE && isCyclicVisit(i, visited, adjList)) {
      return true;
    }
  }
  return false;
}

void xLookup(int id, Graph &parents, Ancestors &xTable) {
  xTable[id] = BLACK;
  if (parents[id]->leftParent != nullptr && xTable[parents[id]->leftParent->id] != BLACK) {
    xLookup(parents[id]->leftParent->id, parents, xTable);
  }
  if (parents[id]->rightParent != nullptr && xTable[parents[id]->rightParent->id] != BLACK) {
    xLookup(parents[id]->rightParent->id, parents, xTable);
  }
}

void yCleanup(int id, Graph &parents, Ancestors &yTable) {
  yTable[id] = BLACK;
  if (parents[id]->leftParent != nullptr && yTable[parents[id]->leftParent->id] != BLACK) {
    yCleanup(parents[id]->leftParent->id, parents, yTable);
  }
  if (parents[id]->rightParent != nullptr && yTable[parents[id]->rightParent->id] != BLACK) {
    yCleanup(parents[id]->rightParent->id, parents, yTable);
  }
}

void yLookup(int id, Graph &parents, Ancestors &xTable, Ancestors &yTable) {
  if (xTable[id] == BLACK && yTable[id] == WHITE) {
    yTable[id] = GRAY;
    if (parents[id]->leftParent != nullptr && yTable[parents[id]->leftParent->id] != BLACK) yCleanup(parents[id]->leftParent->id, parents, yTable);
    if (parents[id]->rightParent != nullptr && yTable[parents[id]->rightParent->id] != BLACK) yCleanup(parents[id]->rightParent->id, parents, yTable);
  } else {
    yTable[id] = BLACK;
    if (parents[id]->leftParent != nullptr && yTable[parents[id]->leftParent->id] == WHITE) yLookup(parents[id]->leftParent->id, parents, xTable, yTable);
    if (parents[id]->rightParent != nullptr && yTable[parents[id]->rightParent->id] == WHITE) yLookup(parents[id]->rightParent->id, parents, xTable, yTable);
  }
}

void lca(int noNodes, int x, int y, Graph &parents) {
  Ancestors xTable(noNodes + 1, WHITE); // they all start at WHITE
  Ancestors yTable(noNodes + 1, WHITE); // they all start at WHITE
  xLookup(x, parents, xTable);
  yLookup(y, parents, xTable, yTable);
  // sort yTable's keys that are GRAY
  std::vector<Node> grayKeys;
  for (Node i = 0; i < (int) yTable.size(); i++) {
    if (yTable[i] == GRAY) grayKeys.push_back(i);
  }
  std::sort(grayKeys.begin(), grayKeys.end());
  for (Node v: grayKeys) {
    std::cout << v << " ";
  }
  if (grayKeys.size() == 0) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;
  int noNodes, noEdges;
  std::cin >> noNodes >> noEdges;

  // parents[i] = [u, v] means that u and v are i's parents
  Graph parents = Graph(noNodes + 1);
  // actually allocate the amount of vertices needed
  for (int i = 0; i <= noNodes; i++) {
    parents[i] = new Vertex();
  }

  Node x, y;
  int readEdges;
  for (readEdges = 0; readEdges < noEdges && std::cin >> x >> y; readEdges++) {
    if (parents[y]->parentAmount == MAX_PARENTS) {
      std::cout << 0 << std::endl;
      return 0;
    }
    if (parents[y]->parentAmount == 0) parents[y]->leftParent = parents[x];
    else parents[y]->rightParent = parents[x];
    parents[y]->parentAmount++;
  }

  for (Node i = 0; i <= noNodes; i++) {
    parents[i]->id = i;
  }

  if (readEdges < noEdges || isCyclic(noNodes, parents)) {
    std::cout << 0 << std::endl;
    return 0;
  }
  lca(noNodes, n, m, parents);
  return 0;
}
