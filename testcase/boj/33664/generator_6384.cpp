#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for size
    int N = rnd.next(1, 12);
    int M = rnd.next(1, min(N, 10));

    // Generate unique item names
    vector<string> names;
    names.reserve(N);
    set<string> used;
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < N; i++) {
        string s;
        do {
            int L = rnd.wnext(14, -1) + 1;  // length between 1 and 15, bias to small
            s.clear();
            for (int j = 0; j < L; j++) {
                s += rnd.any(chars);
            }
        } while (used.count(s));
        used.insert(s);
        names.push_back(s);
    }

    // Generate prices (0 or up to maxPrice)
    int maxPrice = 1000000;  // keep small for hand verification
    vector<int> prices(N);
    for (int i = 0; i < N; i++) {
        int t = rnd.next(0, 9);
        if (t == 0) {
            prices[i] = 0;
        } else if (t == 1) {
            prices[i] = rnd.next(maxPrice / 2 + 1, maxPrice);
        } else {
            prices[i] = rnd.next(0, maxPrice);
        }
    }

    // Choose M distinct items to purchase
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end());
    vector<int> buy(perm.begin(), perm.begin() + M);

    // Compute sum of chosen prices
    long long sumPrices = 0;
    for (int idx : buy) sumPrices += prices[idx];

    // Decide acceptable or unacceptable
    bool ok = (sumPrices == 0 ? true : rnd.next(0, 1));
    long long B;
    if (ok) {
        // budget at least sumPrices
        int extra = rnd.next(0, maxPrice / 2);
        B = sumPrices + extra;
    } else {
        // budget just under sumPrices
        int low = max(0LL, sumPrices - maxPrice / 2);
        int high = sumPrices - 1;
        B = rnd.next(low, high);
    }

    // Output
    println(B, N, M);
    for (int i = 0; i < N; i++) {
        println(names[i], prices[i]);
    }
    for (int idx : buy) {
        println(names[idx]);
    }

    return 0;
}
