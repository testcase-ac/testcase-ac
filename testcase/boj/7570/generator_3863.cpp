#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N
    int N = rnd.next(1, 10);
    // Prepare base permutation 1..N
    vector<int> p(N);
    iota(p.begin(), p.end(), 1);

    // Choose a generation mode for diversity
    // 0: already sorted
    // 1: reversed
    // 2: completely random
    // 3: random but ensure a consecutive-value run
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        // do nothing, already sorted
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        shuffle(p.begin(), p.end());
    } else {
        // mode == 3: inject a run of consecutive values of random length L
        int L = rnd.next(1, N);
        int startVal = rnd.next(1, N - L + 1);
        // Build block of values [startVal .. startVal+L-1]
        vector<int> block;
        vector<bool> inBlock(N+1, false);
        for (int v = startVal; v < startVal + L; v++) {
            block.push_back(v);
            inBlock[v] = true;
        }
        // Other values
        vector<int> other;
        for (int v = 1; v <= N; v++) {
            if (!inBlock[v]) other.push_back(v);
        }
        shuffle(other.begin(), other.end());
        // Decide block start position
        int pos = rnd.next(0, N - L);
        vector<int> q(N);
        int oi = 0;
        for (int i = 0; i < N; i++) {
            if (i >= pos && i < pos + L) {
                q[i] = block[i - pos];
            } else {
                q[i] = other[oi++];
            }
        }
        p = q;
    }

    // Output
    println(N);
    println(p);
    return 0;
}
