#include <iostream>
#include <vector>
#include <string>

#define max(a, b) (a > b ? a : b)
#define FIRST 1

int parseVector(std::vector<int> &v);
void printResults(int longest, int amount);
void solveFirstProblem();
void solveSecondProblem();

int main() {
  int numSequences;
  std::cin >> numSequences;
  std::cin.ignore(); // consumes newline

  numSequences == FIRST ? solveFirstProblem() : solveSecondProblem();
  
  return 0;
}

int parseVector(std::vector<int> &v) {
  int numElements = 0;
  int num;
  char delimiter;
  bool keepReading = true;
  while (keepReading && scanf("%d%c", &num, &delimiter) != EOF) {
    v.push_back(num);
    if (delimiter == '\n') {
      keepReading = false;
    }
    numElements++;
  }
  return numElements;
}

void printResults(int longest, int amount) {
  std::cout << longest << " " << amount << std::endl;
}

// find longest increasing subsequence in an array
// output the longest increasing subsequence size AND the amount of increasing subsequences with that size
// algorithm is based on patience sorting, can be found at:
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
void solveFirstProblem() {
  std::vector<int> elements;
  int numElements = parseVector(elements);

  if (numElements == 0) {
    printResults(0, 0);
    return;
  }

  int longestIncSubsequence = 0;
  int numIncSubsequences = 1;
  std::vector<int> piles(numElements, 0);

  printResults(longestIncSubsequence, numIncSubsequences);
}

void solveSecondProblem() {
  return;
}