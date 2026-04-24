#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of sizes
    int m = rnd.next(1, 8);
    // Maximum extra disks above the mandatory one per size
    int rem_max = 20 - m;
    // Bias extra disks distribution for diversity
    int t = rnd.next(-2, 2);
    int rem = rnd.wnext(rem_max + 1, t); // rem in [0, rem_max]
    // Distribute extra disks randomly among sizes
    vector<int> extra(m, 0);
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, m - 1);
        extra[idx]++;
    }
    vector<int> k(m);
    for (int i = 0; i < m; i++) {
        k[i] = 1 + extra[i];
    }
    // Assign colors, ensure at least one of each if possible
    vector<char> color(m);
    if (m >= 3) {
        vector<int> idx(m);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        color[idx[0]] = 'R';
        color[idx[1]] = 'G';
        color[idx[2]] = 'B';
        for (int i = 3; i < m; i++) {
            color[idx[i]] = rnd.any(string("RGB"));
        }
    } else {
        for (int i = 0; i < m; i++) {
            color[i] = rnd.any(string("RGB"));
        }
    }
    // Output
    println(m);
    for (int i = 0; i < m; i++) {
        println(color[i], k[i]);
    }
    return 0;
}
