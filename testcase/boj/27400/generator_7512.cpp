#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: bias towards small or large within [1,15]
    int Nmax = 15;
    int tN = rnd.next(-2, 2);
    int N = rnd.wnext(Nmax, tN) + 1; // N in [1, Nmax]

    // Total possible subarrays
    int totalRanges = N * (N + 1) / 2;
    // Limit M to keep input hand-verifiable
    int Mlimit = min(totalRanges, 60);
    int tM = rnd.next(-1, 1);
    int M = rnd.wnext(Mlimit, tM) + 1; // M in [1, Mlimit]

    vector<array<int,4>> cons;
    cons.reserve(M);
    for (int i = 0; i < M; i++) {
        int l = rnd.next(0, N - 1);
        int r = rnd.next(l, N - 1);
        int len = r - l + 1;
        // Hyper-parameter for k: bias towards edges or middle
        int tK = rnd.next(-2, 2);
        int k = rnd.wnext(len, tK) + 1; // k in [1, len]
        int value = rnd.next(0, 1);
        cons.push_back({l, r, k, value});
    }
    // Shuffle to avoid ordered patterns
    shuffle(cons.begin(), cons.end());

    // Output
    println(N, M);
    for (auto &c : cons) {
        println(c[0], c[1], c[2], c[3]);
    }
    return 0;
}
