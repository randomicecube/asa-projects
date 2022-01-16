#include <iostream>
#include <vector>
#include <map>

typedef int Node;
typedef std::map<Node, std::vector<Node>> Graph;
typedef std::map<Node, int> Distances;

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
    if (cycleFound(pair.first, visited, inStack, adjList)) {
      return true;
    }
  }
  return false;
}

void lookup(int time, Node x, Graph &parents, Distances &lookupTimeTable) {
  lookupTimeTable[x] = time;
  for (Node xParent : parents[x]) {
    lookup(time + 1, xParent, parents, lookupTimeTable);
  }
}

void lca(Node x, Node y, Graph &parents) {
  Distances xLookup;
  Distances yLookup;
  Distances overallLookup;
  int minDistance = 0;
  bool printed = false;
  lookup(1, x, parents, xLookup);
  // print lookup table
  std::cout << "x lookup table: " << std::endl;
  for (auto pair: xLookup) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
  printf("...\n");
  std::cout << "y lookup table: " << std::endl;
  lookup(1, y, parents, yLookup);
  // print lookup table
  for (auto pair: yLookup) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
  printf("...\n");
  for (auto pair: xLookup) {
    if (yLookup[pair.first] != 0) {
      overallLookup[pair.first] = std::min(pair.second, yLookup[pair.first]);
      if (minDistance == 0 || overallLookup[pair.first] < minDistance) {
        minDistance = overallLookup[pair.first];
      }
    }
  }
  // print overallLookup table
  std::cout << "commonLookup: " << std::endl;
  for (auto pair: overallLookup) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
  // printf("overallLookup[2] is %d\n", overallLookup[2]);
  // printf("overallLookup[4] is %d\n", overallLookup[4]);
  printf("minDistance is %d\n", minDistance);
  for (auto pair: overallLookup) {
    if (pair.second == minDistance) {
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
