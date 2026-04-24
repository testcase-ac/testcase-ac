#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of plots
    int N = rnd.next(1, 10);
    int type = rnd.next(0, 2); // 0=random, 1=anti-correlated, 2=correlated
    vector<pair<int,int>> plots(N);

    if (type == 0) {
        // completely random
        for (int i = 0; i < N; i++) {
            int w = rnd.next(1, 20);
            int h = rnd.next(1, 20);
            plots[i] = {w, h};
        }
    } else {
        // generate separate lists then sort
        vector<int> W(N), H(N);
        for (int i = 0; i < N; i++) {
            W[i] = rnd.next(1, 20);
            H[i] = rnd.next(1, 20);
        }
        sort(W.begin(), W.end());
        if (type == 1) {
            // anti-correlated heights
            sort(H.begin(), H.end(), greater<int>());
        } else {
            // correlated heights
            sort(H.begin(), H.end());
        }
        for (int i = 0; i < N; i++) {
            plots[i] = {W[i], H[i]};
        }
    }

    // Randomly shuffle input order for more diversity
    if (rnd.next(0, 1) == 1) {
        shuffle(plots.begin(), plots.end());
    }

    // Possibly introduce some equal widths or heights by copying neighbors
    if (N >= 2 && rnd.next(0, 1)) {
        int idx = rnd.next(0, N - 2);
        if (rnd.next(0, 1))
            plots[idx + 1].first = plots[idx].first;
        else
            plots[idx + 1].second = plots[idx].second;
    }

    // Output
    println(N);
    for (auto &p : plots) {
        println(p.first, p.second);
    }
    return 0;
}
