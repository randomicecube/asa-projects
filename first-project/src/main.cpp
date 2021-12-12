#include <iostream>
#include <vector>
#include <bits/stdc++.h>

typedef unsigned long long ll;
typedef ll Card;
typedef std::vector<Card> Pile;

#define FIRST 1
#define NOT_FOUND (ll) -1

ll parseVector(std::vector<Card> &v);
void addLeftmostPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, Card card);
void addOtherPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, ll pileIndex, Card card);
void solveLIS(std::vector<Card> &v, ll noElements); // LIS standing for Longest Increasing Subsequence
void solveLCIS(std::vector<ll> &v1, std::vector<ll> &v2, ll noElements1, ll noElements2); // LCIS standing for Longest Common Increasing Subsequence

int main() {
  int numSequences = FIRST;
  std::cin >> numSequences;
  std::cin.ignore(); // consumes newline

  if (numSequences == FIRST) {
    std::vector<Card> v;
    int noElements = parseVector(v);
    solveLIS(v, noElements);
  } else {
    ll noElements1, noElements2;
    std::vector<ll> v1, v2;
    noElements1 = parseVector(v1);
    noElements2 = parseVector(v2);
    solveLCIS(v1, v2, noElements1, noElements2);
  }
  
  return 0;
}

ll parseVector(std::vector<Card> &v) {
  ll numElements = 0;
  ll num;
  char delimiter;
  bool keepReading = true;
  while (keepReading && scanf("%lld%c", &num, &delimiter) != EOF) {
    v.push_back(num);
    if (delimiter == '\n') {
      keepReading = false;
    }
    numElements++;
  }
  return numElements;
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
  ll cardIndex = upper_bound(
    piles[pileIndex - 1].begin(),
    piles[pileIndex - 1].end(),
    card,
    std::greater<ll>()
  ) - piles[pileIndex - 1].begin();
  cardIndex--; // we always want the card that is just "under" the one we found

  ll sum = cumSums[pileIndex - 1].back();
  ll pilesSize = piles.size();
  
  if (cardIndex != NOT_FOUND) {
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

void solveLIS(std::vector<ll> &v, ll noElements) {
  if (noElements == 0) {
    std::cout << 0 << 0 << std::endl;
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

  std::cout << piles.size() << " " << cumSums.back().back() << std::endl;
}

void solveLCIS(std::vector<ll> &v1, std::vector<ll> &v2, ll noElements1, ll noElements2) {
  // each table element will be the max LCS ending in that index's element in v2
  // if an element is not in both vectors, it will be 0 in the table!
  if (noElements1 == 0 || noElements2 == 0) {
    std::cout << 0 << std::endl;
    return;
  }
  
  std::vector<ll> lengths = std::vector<ll>(noElements2, 0);

  for (ll i = 0; i < noElements1; i++) {
    for (ll j = 0, currMax = 0; j < noElements2; j++) {
      if (v1[i] > v2[j]) {
        currMax = std::max(lengths[j], currMax); 
      } else if (v1[i] == v2[j]) {
        lengths[j] = std::max(lengths[j], currMax + 1);
      }
    }
  }

  ll maxElement = *std::max_element(lengths.begin(), lengths.end());
  std::cout << maxElement << std::endl;
}