/*************************************************************
 * IST - ASA 21/22
 * Group - al038
 * Diogo Melita, 99202
 * Diogo Gaspar, 99207
 ************************************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

typedef int Node;
typedef enum { WHITE, GRAY, BLACK } Color;
typedef std::unordered_map<Node, std::vector<Node>> Graph;
typedef std::unordered_map<Node, Color> Ancestors;

bool isCyclicUtil(Node v, std::vector<Color> &visited, Graph &adjList) {
  visited[v] = GRAY;
  for (Node u: adjList[v]) {
    if (
      visited[u] == GRAY ||
      (visited[u] == WHITE && isCyclicUtil(u, visited, adjList))  
    ) {
      return true;
    }
  }
  visited[v] = BLACK;
  return false;
}

bool isCyclic(int noNodes, Graph &adjList) {
  std::vector<Color> visited(noNodes, WHITE);
  for (Node v: visited) {
    if (v == WHITE) {
      if (isCyclicUtil(v, visited, adjList)) {
        return true;
      }
    }
  }
  return false;
}

void xLookup(Node x, Graph &parents, Ancestors &xTable) {
  xTable[x] = BLACK;
  for (Node xParent : parents[x]) {
    if(xTable[xParent] != BLACK) xLookup(xParent, parents, xTable);
  }
}

void yCleanup(Node y, Graph &parents, Ancestors &yTable) {
  yTable[y] = BLACK;
  for (Node yParent : parents[y]) {
    if (yTable[yParent] != BLACK) yCleanup(yParent, parents, yTable);
  }
}

void yLookup(Node y, Graph &parents, Ancestors &xTable, Ancestors &yTable) {
  if (xTable[y] == BLACK && yTable[y] != BLACK) {
    yTable[y] = WHITE;
    for (Node yParent : parents[y]) {
      if (yTable[y] != BLACK) yCleanup(yParent, parents, yTable);
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
  // sort yTable's keys that are WHITE
  std::vector<Node> whiteKeys;
  for (auto pair: yTable) {
    if (pair.second == WHITE) whiteKeys.push_back(pair.first);
  }
  std::sort(whiteKeys.begin(), whiteKeys.end());
  for (Node v: whiteKeys) {
    std::cout << v << " ";
  }
  if (whiteKeys.size() == 0) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  getchar();
  int noNodes, noEdges;
  scanf("%d %d", &noNodes, &noEdges);
  
  // parents[i] = [u, v] means that u and v are i's parents
  Graph parents;
  // adjList[i] = [j, k] means that there is an edge from i to j and from i to k
  Graph adjList;

  for (int i = 0; i < noEdges; i++) {
    getchar();
    int x, y;
    scanf("%d %d", &x, &y);
    if (parents[y].size() == 2) { // we would be adding a third parent
      std::cout << 0 << std::endl;
      return 0;
    }
    parents[y].push_back(x); // x is y's parent
    adjList[x].push_back(y); // y is x's child
  }

  if (isCyclic(noNodes, adjList)) {
    std::cout << 0 << std::endl;
    return 0;
  }

  lca(n, m, parents);
  return 0;
}
