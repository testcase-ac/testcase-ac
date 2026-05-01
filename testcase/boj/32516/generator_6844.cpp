#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in [1,30]
    int N = rnd.next(1, 30);
    string T(N, '?');

    // Hyper-parameter for uneven distributions
    vector<int> tOpts = {-2, -1, 0, 1, 2};
    int t = rnd.any(tOpts);

    // Choose pattern type
    int type = rnd.next(0, 4);
    if (type == 1 && N <= 1) {
        // avoid conflict type for N<=1
        type = rnd.next(0, 4);
        while (type == 1) type = rnd.next(0, 4);
    }

    string letters = "abcdefghijklmnopqrstuvwxyz";

    if (type == 0) {
        // symmetric known pairs
        int maxPairs = (N + 1) / 2;
        int L = rnd.wnext(maxPairs + 1, t); // [0, maxPairs]
        vector<int> pos(maxPairs);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());
        pos.resize(L);
        for (int i : pos) {
            char c = rnd.any(letters);
            T[i] = c;
            T[N - 1 - i] = c;
        }
    } else if (type == 1) {
        // asymmetric conflict at one mirror pair
        int maxIdx = N / 2 - 1;
        int i = rnd.next(0, maxIdx);
        char c1 = rnd.any(letters);
        char c2 = rnd.any(letters);
        while (c2 == c1) c2 = rnd.any(letters);
        T[i] = c1;
        T[N - 1 - i] = c2;
        // maybe add a few more knowns
        int extras = rnd.next(0, N / 4);
        for (int k = 0; k < extras; k++) {
            int p = rnd.next(0, N - 1);
            if (T[p] == '?') {
                T[p] = rnd.any(letters);
            }
        }
    } else if (type == 2) {
        // prefix known
        int L = rnd.next(1, N);
        for (int i = 0; i < L; i++) {
            T[i] = rnd.any(letters);
        }
    } else if (type == 3) {
        // suffix known
        int L = rnd.next(1, N);
        for (int i = N - L; i < N; i++) {
            T[i] = rnd.any(letters);
        }
    } else {
        // scattered random knowns
        int K = rnd.wnext(N + 1, t); // [0, N]
        vector<int> pos(N);
        iota(pos.begin(), pos.end(), 0);
        shuffle(pos.begin(), pos.end());
        pos.resize(K);
        for (int i : pos) {
            T[i] = rnd.any(letters);
        }
    }

    // Output
    printf("%d\n%s\n", N, T.c_str());
    return 0;
}
