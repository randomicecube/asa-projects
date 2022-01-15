#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

typedef int Node;

int lookupTime = -1;

bool cyclesExist(std::unordered_map<Node, std::vector<Node>> adjList) {
  int v = adjList.size();
  std::vector<int> inDegree(v, 0);
  std::queue<Node> q;

  for (auto pair : adjList) { // O(V + E)
    for (Node v : pair.second) {
      inDegree[v]++;
    }
  }

  for (int i = 0; i < v; i++) { // O(V)
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  int count = 1;
  while (!q.empty()) { // O (V + E)
    Node u = q.front();
    q.pop();
    for (Node v : adjList[u]) {
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
        count++;
      }
    }
  }
  return count != v;
}

bool invalidParents(Node x, Node y, std::unordered_map<Node, std::vector<Node>> &parents) {
  // graph's invalid if there are already 2 parents for x
  // or if both x and the other parent of y have the same parent
  int noParents = parents[x].size();
  if (noParents == 2) { // we would be adding a third parent
    return true;
  }
  if (noParents == 1) {
    for (Node yParent : parents[y]) {
      for (Node yGrandParent : parents[yParent]) {
        if (yGrandParent == parents[x][0]) {
          return true;
        }
      }
    }
  }
  return false;
}

void xLookup(int time, Node x, std::unordered_map<Node, std::vector<Node>> &parents, std::unordered_map<Node, int> &xSearch) {
  xSearch[x] = time;
  if (parents[x].size() == 0) {
    return;
  }
  for (Node xParent : parents[x]) {
    xLookup(time + 1, xParent, parents, xSearch);
  }
}

int yLookup(Node y, std::unordered_map<Node, std::vector<Node>> &parents, std::unordered_map<Node, int> &xSearch) {
  if (parents[y].size() == 0 && xSearch[y] == 0) {
    std::cout << "-";
    return -1;
  }
  if ((lookupTime == -1 || xSearch[y] <= lookupTime) && xSearch[y] > 0) {
    if (lookupTime == -1) { // first Node to print
      lookupTime = xSearch[y];
    } else { // not the first, print the space
      std::cout << " ";
    }
    std::cout << y;
    return 0;
  }
  for (Node yParent : parents[y]) {
    yLookup(yParent, parents, xSearch);
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int noNodes, noEdges;
  std::cin >> noNodes >> noEdges;
  
  // parents[i] = [u, v] means that u and v are i's parents
  std::unordered_map<Node, std::vector<Node>> parents;
  std::unordered_map<Node, std::vector<Node>> adjList;

  for (int i = 0; i < noEdges; i++) {
    int x, y;
    std::cin >> x >> y;
    if (invalidParents(x, y, parents)) {
      std::cout << 0 << std::endl;
      return 0;
    }
    parents[y].push_back(x); // x is y's parent
    adjList[x].push_back(y); // y is x's child
  }

  if (cyclesExist(adjList)) {
    std::cout << 0 << std::endl;
    return 0;
  }

  std::unordered_map<Node, int> xSearch;
  xLookup(1, n, parents, xSearch);
  yLookup(m, parents, xSearch);
  std::cout << std::endl;
  return 0;
}
