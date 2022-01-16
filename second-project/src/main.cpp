#include <iostream>
#include <vector>
#include <unordered_map>

typedef int Node;

int lookupTime = -1;

bool cycleFound(Node v, std::vector<bool> &visited, std::vector<bool> &inStack, std::unordered_map<Node, std::vector<Node>> &adjList) {
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

bool cyclesExist(int noNodes, std::unordered_map<Node, std::vector<Node>> &adjList) {
  std::vector<bool> visited(noNodes);
  std::vector<bool> inStack(noNodes);
  for (auto pair: adjList) {
    visited[pair.first] = false;
    inStack[pair.first] = false;
  }
  for (auto pair: adjList) { // indexed from 1
    if (cycleFound(pair.first, visited, inStack, adjList)) {
      return true;
    }
  }
  return false;
}

void lookup(int time, Node x, std::unordered_map<Node, std::vector<Node>> &parents, std::unordered_map<Node, int> &lookupTimeTable) {
  if (lookupTimeTable[x] == 0 || time < lookupTimeTable[x]) {
    lookupTimeTable[x] = time;
  }
  for (Node xParent : parents[x]) {
    lookup(time + 1, xParent, parents, lookupTimeTable);
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int noNodes, noEdges;
  std::cin >> noNodes >> noEdges;
  
  // parents[i] = [u, v] means that u and v are i's parents
  std::unordered_map<Node, std::vector<Node>> parents;
  // adjList[i] = [j, k] means that there is an edge from i to j and from i to k
  std::unordered_map<Node, std::vector<Node>> adjList;

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


  std::unordered_map<Node, int> xSearch;
  std::unordered_map<Node, int> ySearch;
  lookup(1, n, parents, xSearch);
  lookup(1, m, parents, ySearch);
  // print xSearch
  for (auto pair: xSearch) {
    printf("printing xSearch: %d %d\n", pair.first, pair.second);
  }
  printf("-----------------\n");
  // print ySearch
  for (auto pair: ySearch) {
    printf("printing ySearch: %d %d\n", pair.first, pair.second);
  }
  std::cout << std::endl;
  return 0;
}
