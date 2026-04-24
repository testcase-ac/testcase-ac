#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 2 and 12 for hand-checkable sizes
    int N = rnd.next(2, 12);
    vector<int> p(N);

    // Mode for diversity
    // 0: fully random permutation
    // 1: completely reversed
    // 2: suffix already sorted (p[i]=i for last L)
    // 3: prefix already sorted (p[i]=i for first K)
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // full random
        for (int i = 0; i < N; i++) p[i] = i + 1;
        shuffle(p.begin(), p.end());
    } else if (mode == 1) {
        // reversed
        for (int i = 0; i < N; i++) p[i] = N - i;
    } else if (mode == 2) {
        // suffix sorted of length L
        int L = rnd.next(1, N - 1);
        // prefix positions [0..N-L-1] get values [1..N-L] shuffled
        for (int i = 0; i < N - L; i++) p[i] = i + 1;
        shuffle(p.begin(), p.begin() + (N - L));
        // suffix positions [N-L..N-1] are sorted i+1
        for (int i = N - L; i < N; i++) p[i] = i + 1;
    } else {
        // prefix sorted of length K
        int K = rnd.next(1, N - 1);
        // prefix [0..K-1] sorted
        for (int i = 0; i < K; i++) p[i] = i + 1;
        // suffix [K..N-1] are values [K+1..N] shuffled
        for (int i = K; i < N; i++) p[i] = i + 1;
        shuffle(p.begin() + K, p.end());
    }

    // Output the test case
    println(N);
    println(p);
    return 0;
}
