#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for n: small to medium for manual check
    int n = rnd.next(1, 12);
    // Hyper-parameter for m: up to 2*n but ≤20
    int m = rnd.next(1, min(2 * n, 20));
    // Generate initial orientation string
    string init(n, '0');
    for (int i = 0; i < n; i++) {
        init[i] = char('0' + rnd.next(0, 1));
    }
    // Generate m switch definitions with varied sparsity
    vector<string> ops(m, string(n, '0'));
    for (int i = 0; i < m; i++) {
        bool sparse = rnd.next() < 0.5;
        int cnt;
        if (sparse) {
            // few flips
            int maxFew = n / 4;
            cnt = rnd.next(0, maxFew);
        } else {
            // many flips
            int minMany = (3 * n) / 4;
            cnt = rnd.next(minMany, n);
        }
        // choose cnt distinct positions to flip
        vector<int> pos(n);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());
        for (int j = 0; j < cnt; j++) {
            ops[i][pos[j]] = '1';
        }
    }
    // Output the generated test case
    println(n, m);
    println(init);
    for (auto &s : ops) println(s);
    return 0;
}
