#include <iostream>
#include <vector>
#include <unordered_map>

typedef int Vertex;
typedef std::unordered_map<Vertex, std::vector<Vertex>> Graph;

int sccAmount(Graph &graph, int n);
bool cyclesExist(Graph &graph, int n);
void findLowestCommonAncestor(Graph &graph, int n, int m);

int main() {
  Vertex n, m;
  std::cin >> n >> m;

  int noVertexes, noEdges;
  std::cin >> noVertexes >> noEdges; 

  Graph genTree;

  for (int i = 0; i < noEdges; i++) {
    Vertex parent, child;
    std::cin >> parent >> child;
    genTree[parent].push_back(child);
  }

  if (cyclesExist(genTree, noVertexes)) {
    std::cout << 0 << std::endl;
    return 0;
  }

  findLowestCommonAncestor(genTree, n, m);

  return 0;
}

/* 
 * Finds the amount of strongly connected components in the graph
 * If there are less than n scc's, there is a cycle
 */
int sccAmount(Graph &graph, int n) {
  int n = 0;
  return n;
}

/*
 * Checks if there are cycles in the graph
 * Is aided by sccAmount for that
 */
bool cyclesExist(Graph &graph, int n) {
  // if there are != than n SCCs, there is at least one cycle
  // we check != than and not just < because we need to check
  // whether all vertexes are attainable or not
  // find SCCs in graph
  return false;
}

/*
 * Finds the lowest common ancestor of two nodes
 */
void findLowestCommonAncestor(Graph &graph, Vertex n, Vertex m) {
  printf("test\n");
}