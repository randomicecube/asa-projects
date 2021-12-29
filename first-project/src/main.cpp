/*************************************************************
 * IST - ASA 21/22
 * Group - al038
 * Diogo Melita, 99202
 * Diogo Gaspar, 99207
 ************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

typedef unsigned long ll;
typedef ll Card;
typedef std::vector<Card> Pile;

#define FIRST_PROBLEM 1
#define LEFT_PILE 0
#define NOT_FOUND (ll) -1

ll parseVector(std::vector<Card> &v);
void parseFirstCommonVector(std::vector<Card> &v, std::unordered_map<ll, bool> &m);
ll parseSecondCommonVector(std::vector<Card> &v, std::unordered_map<ll, bool> &m);
void addLeftmostPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, Card card);
void addOtherPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, ll pileIndex, Card card);
void solveLIS(std::vector<Card> &v, ll noElements); // LIS standing for Longest Increasing Subsequence
void solveLCIS(std::vector<ll> &v1, std::vector<ll> &v2, ll noElements2); // LCIS standing for Longest Common Increasing Subsequence

std::vector<ll> generateVector(int size) {
    std::vector<ll> v;
    for (int i = 0; i < size; i++) { v.push_back(rand() % 10000); }
    return v;
}

int main(int argc, char *argv[]) {
  int numSequences = 2;
  // std::cin >> numSequences;
  // std::cin.ignore(); // consumes newline

  if (numSequences == FIRST_PROBLEM) {
		// char *p;
    // ll arg = strtol(argv[1], &p, 10);
    // ll n;
    // std::cin >> n;
    // std::vector<Card> v = generateVector(n);
    std::vector<Card> v;
    ll noElements = parseVector(v);
    solveLIS(v, noElements);
  } else {
    std::vector<Card> v1, v2;
    std::unordered_map<ll, bool> map;
    ll noElements2;
    std::cout << "got to the first" << std::endl;
    parseFirstCommonVector(v1, map);
    std::cout << "got to the second" << std::endl;
    noElements2 = parseSecondCommonVector(v2, map);
    std::cout << "got to the third" << std::endl;
    std::cout << "first vector" << std::endl;
    for (auto i : v1) { std::cout << i << " "; }
    std::cout << std::endl;
    std::cout << "second vector" << std::endl;
    for (auto i : v2) { std::cout << i << " "; }
    std::cout << std::endl;
    solveLCIS(v1, v2, noElements2);
    std::cout << "got to the fourth" << std::endl;
  }
  
  return 0;
}

ll parseVector(std::vector<Card> &v) {
  ll numElements = 0;
  ll num;
  char delimiter;
  while (scanf("%ld%c", &num, &delimiter) != EOF) {
    v.push_back(num);
    numElements++;
    if (delimiter == '\n') {
      return numElements;
    }
  }
	return numElements;
}

void parseFirstCommonVector(std::vector<Card> &v, std::unordered_map<ll, bool> &m) {
  ll numElements = 0;
  ll num;
  char delimiter;
  while (scanf("%ld%c", &num, &delimiter) != EOF) {
    v.push_back(num);
    m[num] = true;
    numElements++;
    if (delimiter == '\n') {
      return;
    }
  }
}

ll parseSecondCommonVector(std::vector<Card> &v, std::unordered_map<ll, bool> &m) {
  ll numElements = 0;
  ll num;
  char delimiter;
  while (scanf("%ld%c", &num, &delimiter) != EOF) {
    if (m[num]) {
      v.push_back(num);
      numElements++;
    }
    if (delimiter == '\n') {
      return numElements;
    }
  }
  return numElements;
}

void addLeftmostPile(std::vector<Pile> &piles, std::vector<std::vector<ll>> &cumSums, Card card) {
  if (piles.size() == 0) {
    piles.push_back({card});
    cumSums.push_back({1});
  } else {
    ll sum = piles[LEFT_PILE].size() + 1;
    piles[LEFT_PILE].push_back(card);
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
  std::vector<Pile> piles;
  std::vector<std::vector<ll>> cumSums;
  for (Card card: v) {
    ll pileIndex = lower_bound(
      piles.begin(),
      piles.end(),
      card,
      [](const Pile &pile, Card card) { return pile.back() < card; }
    ) - piles.begin();

		if (pileIndex == LEFT_PILE) {
			addLeftmostPile(piles, cumSums, card);
		} else {
			addOtherPile(piles, cumSums, pileIndex, card);
  	}
	}

  // std::cout << piles.size() << " " << cumSums.back().back() << '\n';
}

void solveLCIS(std::vector<ll> &v1, std::vector<ll> &v2, ll noElements2) {
  // each table element will be the max LCS ending in that index's element in v2
  // if an element is not in both vectors, it will be 0 in the table!
  if (noElements2 == 0) {
    std::cout << 0 << '\n';
    return;
  }
  
  std::vector<ll> lengths = std::vector<ll>(noElements2, 0);
  ll currMax;
	ll secondVecElement;

  for (ll firstVecElement: v1) {
    currMax = 0;
    for (ll j = 0; j < noElements2; j++) {
			secondVecElement = v2[j];
      if (firstVecElement > secondVecElement) {
        currMax = std::max(lengths[j], currMax); 
      } else if (firstVecElement == secondVecElement) {
        lengths[j] = std::max(lengths[j], currMax + 1);
      }
    }
  }

  ll maxLength = *std::max_element(lengths.begin(), lengths.end());
  std::cout << maxLength << '\n';
}
