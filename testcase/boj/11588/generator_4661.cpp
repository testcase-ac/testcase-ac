#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of ingredients
    int N = rnd.next(1, 10);

    // Build all possible unordered pairs (i, j) with i < j
    vector<pair<int,int>> allPairs;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            allPairs.emplace_back(i, j);
        }
    }

    // Hyper-parameter: inclusion probability for each unique pair
    double includeProb = rnd.next();  // in [0,1)
    vector<pair<int,int>> chosen;
    for (auto &e : allPairs) {
        if (rnd.next() < includeProb) {
            chosen.push_back(e);
        }
    }
    // It's okay if chosen is empty (M=0 case)

    // Hyper-parameter: number of duplicate entries to add (could be negative)
    int dupCount = rnd.next(-3, 3);
    if (dupCount > 0) {
        for (int i = 0; i < dupCount; ++i) {
            if (chosen.empty()) break;
            chosen.push_back(rnd.any(chosen));
        }
    }

    // Hyper-parameter: swap endpoints in each pair with some probability
    double swapProb = rnd.next();
    for (auto &e : chosen) {
        if (rnd.next() < swapProb) {
            swap(e.first, e.second);
        }
    }

    // Shuffle the order of the pairs
    shuffle(chosen.begin(), chosen.end());

    // Output
    int M = chosen.size();
    println(N, M);
    for (auto &e : chosen) {
        println(e.first, e.second);
    }

    return 0;
}
