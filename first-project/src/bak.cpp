#include <iostream>
#include <vector>

#define FIRST 1

class Card {
  int value;
  int count;
  public:
    Card(int value);
    int getValue();
    int getCount();
    void setCount(int count);
};

Card::Card(int value) {
  this->value = value;
}

int Card::getValue() {
  return this->value;
}

int Card::getCount() {
  return this->count;
}

void Card::setCount(int count) {
  this->count = count;
}

int parseVector(std::vector<Card> &v);
void printResults(int longest, int amount);
int binSearchPile(std::vector<std::vector<int>> piles, int target);
void addLeftmostPile(std::vector<std::vector<Card>> &piles, Card card);
void addRightmostMiddlePile(std::vector<std::vector<Card>> &piles, Card card, int value, int pileIndex);
std::vector<std::vector<Card>> pushCardsToPiles(std::vector<Card> cards);
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

// TODO - MAKE A SINGLE BINSEARCH FUNCTION - THIS IS AWFUL AWFUL CODE

// algorithm similar to binary search, returns the leftmost pile where a card can go
int binSearchPiles(std::vector<std::vector<Card>> piles, int target) {
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

int binSearchSinglePile(std::vector<Card> pile, int target) {
  int pileSize = pile.size();
  int left = 0;
  int right = pileSize - 1;
  int mid;
  int backCard;
  while (left <= right) {
    mid = (left + right) / 2;
    backCard = pile[mid].getValue();
    if (backCard == target) {
      return mid;
    } else if (backCard > target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return right;
}

void addLeftmostPile(std::vector<std::vector<Card>> &piles, Card card) {
  if (piles.size() == 0) {
    card.setCount(1);
    piles.push_back({card});
  } else {
    card.setCount(piles[0].back().getCount() + 1);
    piles[0].push_back(card);
  }
}

void addRightmostMiddlePile(std::vector<std::vector<Card>> &piles, Card card, int value, int pileIndex) {
  std::vector<Card> prevPile = piles[pileIndex - 1];
  int cardIndex = binSearchSinglePile(prevPile, value);
  int cumSum = prevPile.back().getCount();
  int pilesSize = piles.size();

  if (cardIndex != -1) {
    cumSum -= prevPile[cardIndex].getCount();
  }

  if (pileIndex == pilesSize) {
    card.setCount(cumSum);
    piles.push_back({card});
  } else {
    cumSum += piles[pileIndex].back().getCount();
    card.setCount(cumSum);
    piles[pileIndex].push_back(card);
  }
}

std::vector<std::vector<Card>> pushCardsToPiles(std::vector<Card> cards) {
  std::vector<std::vector<Card>> piles;
  for (Card card: cards) {
    int value = card.getValue();
    int pileIndex = binSearchPiles(piles, value);
    Card newCard = Card(value);

    if (pileIndex == 0) {
      addLeftmostPile(piles, newCard);
    } else {
      addRightmostMiddlePile(piles, newCard, value, pileIndex);
    }

  }
  return piles;
}

// following patience sorting algorithm
void solveFirstProblem() {
  std::vector<Card> elements;
  if (parseVector(elements) == 0) { // no elements
    printResults(0, 0);
    return;
  }
  std::vector<std::vector<Card>> piles = pushCardsToPiles(elements);
  printResults(piles.size(), piles.back().back().getCount());
}

// find longest common increasing subsequence between two vectors in O(nlogn) time

void solveSecondProblem() {
  std::vector<Card> elements1;
  std::vector<Card> elements2;
  parseVector(elements1);
  parseVector(elements2);
  int amount;
  int length = longestCommonIncreasingSubsequence(elements1, elements2, &amount);
  printResults(length, amount);
}

int longestCommonIncreasingSubsequence(std::vector<Card> &elements1, std::vector<Card> &elements2, int *amount) {
  std::vector<int> lengths;
  for (uint i = 0; i < elements1.size(); i++) {
    int length = 0;
    for (uint j = 0; j < elements2.size(); j++) {
      if (elements1[i].getValue() < elements2[j].getValue()) {
        length = 1;
      }
    }
  }
}