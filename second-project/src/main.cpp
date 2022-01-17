/*************************************************************
 * IST - ASA 21/22
 * Group - al038
 * Diogo Melita, 99202
 * Diogo Gaspar, 99207
 ************************************************************/
#include <iostream>
#include <vector>
#include <map>

typedef int Node;
typedef enum { WHITE, BLACK } Color;
typedef std::map<Node, std::vector<Node>> Graph;
typedef std::map<Node, Color> Ancestors;

bool cycleFound(Node v, std::vector<bool> &visited, std::vector<bool> &inStack, Graph &adjList) {
  if (!visited[v]) {
    visited[v] = true;
    inStack[v] = true;
    for (Node w : adjList[v]) {
      if (!visited[w] && cycleFound(w, visited, inStack, adjList)) {
        return true;
      }
      if (inStack[w]) {
        return true;
      }
    }
  }
  inStack[v] = false;
  return false;
}

bool cyclesExist(int noNodes, Graph &adjList) {
  std::vector<bool> visited(noNodes);
  std::vector<bool> inStack(noNodes);
  for (auto pair: adjList) {
    visited[pair.first] = false;
    inStack[pair.first] = false;
  }
  for (auto pair: adjList) { // indexed from 1
    if (!visited[pair.first] && cycleFound(pair.first, visited, inStack, adjList)) {
      return true;
    }
  }
  return false;
}

void xLookup(Node x, Graph &parents, Ancestors &xTable) {
  xTable[x] = BLACK;
  for (Node xParent : parents[x]) {
    xLookup(xParent, parents, xTable);
  }
}

void yCleanup(Node y, Graph &parents, Ancestors &yTable) {
  yTable[y] = BLACK;
  for (Node yParent : parents[y]) {
    yCleanup(yParent, parents, yTable);
  }
}

void yLookup(Node y, Graph &parents, Ancestors &xTable, Ancestors &yTable) {
  if (xTable[y] == BLACK && yTable[y] != BLACK) {
    yTable[y] = WHITE;
    for (Node yParent : parents[y]) {
      yCleanup(yParent, parents, yTable);
    }
  } else {
    for (Node yParent : parents[y]) {
      yLookup(yParent, parents, xTable, yTable);
    }
  }
}

void lca(Node x, Node y, Graph &parents) {
  Ancestors xTable;
  Ancestors yTable;
  xLookup(x, parents, xTable);
  yLookup(y, parents, xTable, yTable);
  bool printed = false;
  for (auto pair: yTable) {
    if (pair.second == WHITE) {
      std::cout << pair.first << " ";
      printed = true;
    }
  }
  if (!printed) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  int n, m;
  std::cin >> n >> m;
  int noNodes, noEdges;
  std::cin >> noNodes >> noEdges;
  
  // parents[i] = [u, v] means that u and v are i's parents
  Graph parents;
  // adjList[i] = [j, k] means that there is an edge from i to j and from i to k
  Graph adjList;

  for (int i = 0; i < noEdges; i++) {
    int x, y;
    std::cin >> x >> y;
    if (parents[y].size() == 2) { // we would be adding a third parent
      std::cout << 0 << std::endl;
      return 0;
    }
    parents[y].push_back(x); // x is y's parent
    adjList[x].push_back(y); // y is x's child
  }

  if (cyclesExist(noNodes, adjList)) {
    std::cout << 0 << std::endl;
    return 0;
  }

  lca(n, m, parents);
  return 0;
}
