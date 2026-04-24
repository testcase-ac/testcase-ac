#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small even N for hand-checkable cases
    vector<int> possibleN = {2, 4, 6, 8, 10};
    int N = rnd.any(possibleN);

    // Build initial sorted deck of size 2N
    vector<int> deck(2 * N);
    iota(deck.begin(), deck.end(), 1);

    // Hyper-parameter: choose a pattern for Elsie's play order
    int pattern = rnd.next(0, 4);
    switch (pattern) {
    case 0:
        // Fully random
        shuffle(deck.begin(), deck.end());
        break;
    case 1:
        // Already sorted (1..2N)
        break;
    case 2:
        // Reverse sorted (2N..1)
        reverse(deck.begin(), deck.end());
        break;
    case 3: {
        // Alternating low, high, next low, next high...
        vector<int> alt;
        int lo = 1, hi = 2 * N;
        while (lo <= hi) {
            alt.push_back(lo++);
            if (lo <= hi) alt.push_back(hi--);
        }
        deck = alt;
        break;
    }
    case 4: {
        // Random small blocks, then shuffle blocks
        vector<int> base = deck;
        vector<vector<int>> blocks;
        int rem = 2 * N, idx = 0;
        while (rem > 0) {
            int sz = rnd.next(1, rem);
            blocks.emplace_back(base.begin() + idx, base.begin() + idx + sz);
            idx += sz;
            rem -= sz;
        }
        shuffle(blocks.begin(), blocks.end());
        vector<int> mixed;
        for (auto &b : blocks)
            for (int x : b)
                mixed.push_back(x);
        deck = mixed;
        break;
    }
    }

    // Take Elsie's first N cards as her play order
    vector<int> elsie(deck.begin(), deck.begin() + N);

    // Output
    println(N);
    for (int x : elsie)
        println(x);

    return 0;
}
