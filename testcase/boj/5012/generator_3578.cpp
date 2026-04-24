#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small size
    int n = rnd.next(1, 10);
    // pick generation type
    int type = rnd.next(0, 4);
    vector<int> a(n);

    if (type == 0) {
        // random with duplicates, weighted bias
        int t = rnd.next(-1, 1);
        for (int i = 0; i < n; i++) {
            a[i] = 1 + rnd.wnext(n, t);
        }
    } else if (type == 1) {
        // strictly increasing
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
    } else if (type == 2) {
        // strictly decreasing
        for (int i = 0; i < n; i++)
            a[i] = n - i;
    } else if (type == 3) {
        // plateau blocks
        int blocks = rnd.next(1, min(n, 3));
        // distinct values
        vector<int> vals;
        while ((int)vals.size() < blocks) {
            int v = rnd.next(1, n);
            bool ok = true;
            for (int x : vals) if (x == v) { ok = false; break; }
            if (ok) vals.push_back(v);
        }
        // order blocks
        if (rnd.next(0,1) == 0)
            sort(vals.begin(), vals.end());
        else
            sort(vals.begin(), vals.end(), greater<int>());
        // block sizes
        vector<int> bs(blocks, 1);
        int rem = n - blocks;
        for (int i = 0; i < rem; i++) {
            bs[rnd.next(0, blocks-1)]++;
        }
        int pos = 0;
        for (int i = 0; i < blocks; i++) {
            for (int j = 0; j < bs[i]; j++) {
                a[pos++] = vals[i];
            }
        }
    } else if (type == 4) {
        // random permutation
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
        shuffle(a.begin(), a.end());
    }

    // output
    println(n);
    println(a);
    return 0;
}
