#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 250;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(N, -N, N, "a_i");
    inf.readEoln();

    // Check that abs values are a permutation of 1..N (each appears exactly once)
    vector<int> cnt(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        int v = a[i];
        ensuref(v != 0, "Element at position %d is zero, but absolute values must be between 1 and N", i + 1);
        int av = abs(v);
        ensuref(1 <= av && av <= N,
                "Absolute value of element at position %d is %d, which is out of range [1, %d]",
                i + 1, av, N);
        cnt[av]++;
    }
    for (int x = 1; x <= N; ++x) {
        ensuref(cnt[x] == 1,
                "Absolute value %d appears %d times; it must appear exactly once",
                x, cnt[x]);
    }

    inf.readEof();
}
