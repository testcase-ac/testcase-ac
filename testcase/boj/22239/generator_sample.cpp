#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 15);
    int n = rnd.next(1, c);

    vector<int> cards(c);
    for (int i = 0; i < c; ++i) {
        cards[i] = i + 1;
    }
    shuffle(cards.begin(), cards.end());

    vector<vector<int>> constraints(n);
    for (int i = 0; i < n; ++i) {
        constraints[i].push_back(cards[i]);
    }
    for (int i = n; i < c; ++i) {
        constraints[rnd.next(n)].push_back(cards[i]);
    }
    for (auto& personCards : constraints) {
        shuffle(personCards.begin(), personCards.end());
    }

    int mode = rnd.next(4);
    vector<long long> cardValues(c + 1);
    for (int card = 1; card <= c; ++card) {
        cardValues[card] = 1000 + card;
    }

    if (mode == 1 && c >= 2) {
        long long shared = rnd.next(1, 20);
        int duplicatedCards = rnd.next(2, min(c, 6));
        vector<int> chosen = cards;
        shuffle(chosen.begin(), chosen.end());
        for (int i = 0; i < duplicatedCards; ++i) {
            cardValues[chosen[i]] = shared;
        }
    } else if (mode == 2) {
        for (int card = 1; card <= c; ++card) {
            cardValues[card] = rnd.next(1, min(c, 6));
        }
    }

    vector<long long> result;
    if (mode == 3) {
        set<long long> used;
        while ((int)result.size() < c) {
            long long value = rnd.next(1, 1000000);
            if (used.insert(value).second) {
                result.push_back(value);
            }
        }
    } else {
        for (int card = 1; card <= c; ++card) {
            result.push_back(cardValues[card]);
        }
        shuffle(result.begin(), result.end());
    }

    map<long long, int> resultCount;
    for (long long value : result) {
        ++resultCount[value];
    }
    int repeatedOccurrences = 0;
    for (const auto& entry : resultCount) {
        if (entry.second >= 2) {
            repeatedOccurrences += entry.second;
        }
    }
    if (repeatedOccurrences > 6) {
        result.clear();
        for (int i = 0; i < c; ++i) {
            result.push_back(100000 + i);
        }
        int duplicated = min(c, 6);
        long long shared = rnd.next(1, 500);
        for (int i = 0; i < duplicated; ++i) {
            result[i] = shared;
        }
        shuffle(result.begin(), result.end());
    }

    println(n, c);
    println(result);
    for (const auto& personCards : constraints) {
        printf("%d", (int)personCards.size());
        for (int card : personCards) {
            printf(" %d", card);
        }
        printf("\n");
    }
    for (int card = 1; card <= c; ++card) {
        println("ADD", cardValues[card]);
    }

    return 0;
}
