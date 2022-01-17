/*************************************************************
 * IST - ASA 21/22
 * Group - al038
 * Diogo Melita, 99202
 * Diogo Gaspar, 99207
 ************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using Node = int;
using Color = enum { WHITE, GRAY, BLACK };
using Graph = std::vector<std::vector<Node>>;
using Ancestors = std::vector<Color>;

bool isCyclicVisit(Node &v, std::vector<Color> &visited, Graph &adjList) {
  visited[v] = GRAY;
  for (Node u: adjList[v]) {
    if (visited[u] == GRAY || (visited[u] == WHITE && isCyclicVisit(u, visited, adjList))) {
      return true;
    }
  }
  visited[v] = BLACK;
  return false;
}

bool isCyclic(int &noNodes, Graph &adjList) {
  std::vector<Color> visited(noNodes, WHITE);
  for (Node v: visited) {
    if (v == WHITE && isCyclicVisit(v, visited, adjList)) {
      return true;
    }
  }
  return false;
}

void xLookup(Node &x, Graph &parents, Ancestors &xTable) {
  xTable[x] = BLACK;
  for (Node xParent : parents[x]) {
    if(xTable[xParent] != BLACK) xLookup(xParent, parents, xTable);
  }
}

void yCleanup(Node &y, Graph &parents, Ancestors &yTable) {
  yTable[y] = BLACK;
  for (Node yParent : parents[y]) {
    if (yTable[yParent] != BLACK) yCleanup(yParent, parents, yTable);
  }
}

void yLookup(Node &y, Graph &parents, Ancestors &xTable, Ancestors &yTable) {
  if (xTable[y] == BLACK && yTable[y] == WHITE) {
    yTable[y] = GRAY;
    for (Node yParent : parents[y]) {
      if (yTable[yParent] != BLACK) yCleanup(yParent, parents, yTable); // CLEANED IF IT HASN'T ALREADY BEEN
    }
  } else {
    yTable[y] = BLACK;
    for (Node yParent : parents[y]) {
      if (yTable[yParent] != GRAY) yLookup(yParent, parents, xTable, yTable);
    }
  }
}

void lca(Node &x, Node &y, Graph &parents) {
  Ancestors xTable(parents.size() + 1, WHITE);
  Ancestors yTable(parents.size() + 1, WHITE);
  xLookup(x, parents, xTable);
  yLookup(y, parents, xTable, yTable); // they all start at WHITE
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
  Graph parents(noNodes + 1);
  // adjList[i] = [j, k] means that there is an edge from i to j and from i to k
  Graph adjList(noNodes + 1);

  int x, y;
  for (int i = 0; i < noEdges && std::cin >> x >> y; i++) {
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
