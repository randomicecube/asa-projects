#include <iostream>
#include <vector>

#define FIRST 1

class Card {
  Card *next;
  int value;
  public:
    Card(int value) {
      this->value = value;
      this->next = nullptr;
    }
    int getValue() {
      return this->value;
    }
    Card *getNext() {
      return this->next;
    }
    void setNext(Card *next) {
      this->next = next;
    }
};

int parseVector(std::vector<Card> &v);
void printResults(int longest, int amount);
int binSearchPile(std::vector<std::vector<int>> piles, int target);
std::vector<std::vector<Card>> pushCardsToPiles(std::vector<Card> &cards, int cardAmount);
int getPathAmount(std::vector<Card> &pile);
void solveFirstProblem();
void solveSecondProblem();

int main() {
  int numSequences;
  std::cin >> numSequences;
  std::cin.ignore(); // consumes newline

  numSequences == FIRST ? solveFirstProblem() : solveSecondProblem();
  
  return 0;
}

int parseVector(std::vector<Card> &v) {
  int numElements = 0;
  int num;
  char delimiter;
  bool keepReading = true;
  while (keepReading && scanf("%d%c", &num, &delimiter) != EOF) {
    v.push_back(Card(num));
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

// algorithm similar to binary search, returns the leftmost pile where a card can go
int binSearchPile(std::vector<std::vector<Card>> piles, int target) {
  int left = 0;
  int right = piles.size() - 1;
  int mid;
  int backCard;
  while (left <= right) {
    mid = (left + right) / 2;
    backCard = piles[mid].back().getValue();
    if (backCard == target) {
      return mid;
    } else if (backCard < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return left;
}

std::vector<std::vector<Card>> pushCardsToPiles(std::vector<Card> &cards, int cardAmount) {
  std::vector<std::vector<Card>> piles;
  for (Card card: cards) {
    int num = card.getValue();
    int index = binSearchPile(piles, num);
    Card newCard = Card(num);
    if (index != 0) {
      newCard.setNext(&piles[index - 1].back());
    }
    if (index == (int) piles.size()) {
      std::vector<Card> newPile = {newCard};
      piles.push_back(newPile);
      for (Card card: newPile) {
        std::cout << "test" << std::endl;
        std::cout << card.getValue() << " " << (card.getNext() == nullptr ? -1 : card.getNext()->getValue()) << std::endl;
        std::cout << "end test" << std::endl;
      }
    } else {
      for (Card card: piles[index]) {
        std::cout << "test else BEFORE" << std::endl;
        std::cout << card.getValue() << " " << (card.getNext() == nullptr ? -1 : card.getNext()->getValue()) << std::endl;
        std::cout << "end test else BEFORE" << std::endl;
      }
      piles[index].push_back(newCard);
      std::cout << "testing for " << num << std::endl;
      for (Card card: piles[index]) {
        std::cout << "test else" << std::endl;
        std::cout << card.getValue() << " " << (card.getNext() == nullptr ? -1 : card.getNext()->getValue()) << std::endl;
        std::cout << "end test else " << std::endl;
      }
    }
  }
  return piles;
}

int getPathAmount(std::vector<Card> &pile) {
  int paths = pile.size();
  Card *prev = nullptr;
  std::cout << "beginning: paths is " << paths << std::endl;
  for (Card card: pile) {
    std::cout << "card is " << card.getValue() << std::endl;
    if (prev == nullptr) {
      std::cout << "prev is null" << std::endl;
      prev = card.getNext();
    } else if (prev->getValue() != card.getNext()->getValue()){
      std::cout << "brah" << std::endl;
      paths++;
      prev = card.getNext();
    }
    std::cout << "did dis ting fail or " << std::endl;
  }
  std::cout << "end: paths is " << paths << std::endl;
  return paths;
}

// find longest increasing subsequence in an array
// output the longest increasing subsequence size AND the amount of increasing subsequences with that size
// algorithm is based on patience sorting, can be found at:
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
void solveFirstProblem() {
  std::vector<Card> elements;
  int numElements = parseVector(elements);

  if (numElements == 0) {
    printResults(0, 0);
    return;
  }

  std::vector<std::vector<Card>> piles = pushCardsToPiles(elements, numElements);
  std::vector<Card> backPile = piles.back();
  int paths = getPathAmount(backPile);

  for (std::vector<Card> pile: piles) {
    for (Card card: pile) {
      int num = card.getValue();
      int nextValue = card.getNext() == nullptr ? -1 : card.getNext()->getValue();
      std::cout << num << " next " << nextValue << std::endl;
    }
    std::cout << std::endl << "---" << std::endl;
  }

  printResults(piles.size(), paths);
}

void solveSecondProblem() { }