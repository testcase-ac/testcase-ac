#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int M = rnd.next(2, 20);
    int N = rnd.next(1, min(10, M - 1));

    // Generate unique detector positions between 1 and M-1
    vector<int> pos;
    for (int i = 1; i < M; ++i) pos.push_back(i);
    shuffle(pos.begin(), pos.end());
    pos.resize(N);
    sort(pos.begin(), pos.end());

    // Generate a consistent C array via random walk with floor at 1
    vector<long long> C(N);
    C[0] = rnd.next(1, 10);
    for (int i = 1; i < N; ++i) {
        int delta = rnd.next(-5, 10);
        if (C[i-1] + delta < 1) {
            // ensure positivity
            delta = rnd.next(0, 10);
        }
        C[i] = C[i-1] + delta;
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(pos[i], C[i]);
    }
    return 0;
}
