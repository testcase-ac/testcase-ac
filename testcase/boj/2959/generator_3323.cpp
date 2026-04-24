#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to choose type of multiset
    int type = rnd.next(1, 10);
    vector<int> a(4);
    if (type <= 3) {
        // all distinct
        vector<int> pool(10);
        iota(pool.begin(), pool.end(), 1);
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < 4; i++) a[i] = pool[i];
    } else if (type <= 6) {
        // one pair
        int v = rnd.next(1, 10);
        set<int> used = {v};
        vector<int> others;
        while (others.size() < 2) {
            int x = rnd.next(1, 10);
            if (!used.count(x)) {
                used.insert(x);
                others.push_back(x);
            }
        }
        a = {v, v, others[0], others[1]};
    } else if (type <= 8) {
        // two pairs
        vector<int> vals;
        while (vals.size() < 2) {
            int x = rnd.next(1, 10);
            if (find(vals.begin(), vals.end(), x) == vals.end())
                vals.push_back(x);
        }
        a = {vals[0], vals[0], vals[1], vals[1]};
    } else if (type == 9) {
        // triple
        int v = rnd.next(1, 10);
        int u;
        do { u = rnd.next(1, 10); } while (u == v);
        a = {v, v, v, u};
    } else {
        // all equal
        int v = rnd.next(1, 10);
        a = {v, v, v, v};
    }
    shuffle(a.begin(), a.end());
    // Output the 4 positive integers
    println(a);
    return 0;
}
