#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rectangles: small for hand-checking
    int N = rnd.next(2, 10);
    // Ensure enough distinct unordered pairs available: U*(U+1)/2 >= N
    double need = (sqrt(1.0 + 8.0*N) - 1.0) / 2.0;
    int U_low = max(2, (int)ceil(need));
    int U = rnd.next(U_low, 20);

    // Hyper-parameters
    double squareProb = rnd.next();            // chance to force a square
    double swapOrientProb = rnd.next();        // chance to swap a,b at output
    bool genChain = rnd.next() < 0.5;          // whether to seed a nesting chain

    set<pair<int,int>> used;
    vector<pair<int,int>> rects;

    if (genChain) {
        int L = rnd.next(1, min(N, U));
        // pick L distinct side-lengths for the larger side
        vector<int> dims(U);
        iota(dims.begin(), dims.end(), 1);
        shuffle(dims.begin(), dims.end());
        dims.resize(L);
        sort(dims.begin(), dims.end(), greater<int>());
        for (int x : dims) {
            int y;
            pair<int,int> key;
            // pick y in [1..x] such that unordered pair is new
            do {
                y = rnd.next(1, x);
                key = minmax(x, y);
            } while (used.count(key));
            used.insert(key);
            rects.emplace_back(x, y);
        }
    }

    // fill the rest with random rectangles, avoiding duplicates
    while ((int)rects.size() < N) {
        int a, b;
        if (rnd.next() < squareProb) {
            int c = rnd.next(1, U);
            a = b = c;
        } else {
            a = rnd.next(1, U);
            b = rnd.next(1, U);
        }
        auto key = minmax(a, b);
        if (used.count(key)) continue;
        used.insert(key);
        rects.emplace_back(a, b);
    }

    // shuffle so the chain is not contiguous
    shuffle(rects.begin(), rects.end());

    // output
    println(N);
    for (auto &p : rects) {
        int a = p.first, b = p.second;
        if (rnd.next() < swapOrientProb) swap(a, b);
        println(a, b);
    }
    return 0;
}
