#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#define FIRST 1

typedef long long ll;
typedef std::vector<ll> Pile;
typedef ll Card; 

ll parseVector(std::vector<Card> &v);
void prllResults(ll longest, ll amount);
void solveLIS(std::vector<Card> &v, ll noElements); // LIS standing for Longest Increasing Subsequence
void solveLCIS(); // LCIS standing for Longest Common Increasing Subsequence
std::vector<ll> generateVector(ll n);

int main() {
  int numSequences;
  std::cin >> numSequences;
  std::cin.ignore(); // consumes newline

  if (numSequences == FIRST) {
    std::vector<Card> v;
    int noElements = parseVector(v);
    solveLIS(v, noElements);
  } else {
    solveLCIS();
  }
  
  return 0;
}

ll parseVector(std::vector<Card> &v) {
  ll numElements = 0;
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

void printResults(ll longest, ll amount) {
  std::cout << longest << " " << amount << std::endl;
}

void addLeftmostPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, Card card) {
  if (piles.size() == 0) {
    piles.push_back({card});
    cumSums.push_back({1});
  } else {
    ll sum = piles[0].size() + 1;
    piles[0].push_back(card);
    cumSums[0].push_back(sum);
  }
}

void addOtherPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, ll pileIndex, Card card) {
  ll cardIndex = lower_bound(
    piles[pileIndex - 1].begin(),
    piles[pileIndex - 1].end(),
    card,
    std::greater<int>()
  ) - piles[pileIndex - 1].begin();
  cardIndex--; // we always want the card that is just "under" the one we found

  ll sum = cumSums[pileIndex - 1].back();
  ll pilesSize = piles.size();
  
  if (cardIndex != -1) {
    sum -= cumSums[pileIndex - 1][cardIndex];
  }

  if (pileIndex == pilesSize) {
    piles.push_back({card});
    cumSums.push_back({sum});
  } else {
    sum += cumSums[pileIndex].back();
    piles[pileIndex].push_back(card);
    cumSums[pileIndex].push_back(sum);
  }
}

void solveLIS(std::vector<ll> &v, ll noElements) { // solve the longest increasing subsequence problem using patience sorting
  if (noElements == 0) {
    printResults(0, 0);
    return;
  }

  std::vector<Pile> piles;
  std::vector<std::vector<ll>> cumSums;
  for (Card card: v) {
    ll pileIndex = lower_bound(
      piles.begin(),
      piles.end(),
      card,
      [](const Pile &pile1, Card card) {
        return pile1.back() < card;
      }
    ) - piles.begin();
    pileIndex == 0 ? addLeftmostPile(piles, cumSums, card) : addOtherPile(piles, cumSums, pileIndex, card);
  }

  printResults(piles.size(), cumSums.back().back());
}

void solveLCIS() { } // TODO: solve the longest common increasing subsequence problem using patience sorting