/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a small N for hand-checkability
    int N = rnd.next(1, 10);
    // Pick a random max absolute value for elements
    vector<int> scales = {5, 10, 20, 100, 100000};
    int maxA = rnd.any(scales);
    // Generate the sequence
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = rnd.next(-maxA, maxA);
    }
    // Decide whether to guarantee at least one solution
    bool forceSolution = rnd.next(0, 1);
    long long S;
    if (forceSolution) {
        // Pick a non-empty random subset and set S to its sum
        int k = rnd.next(1, N);
        vector<int> idx(N);
        for (int i = 0; i < N; ++i) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        S = 0;
        for (int i = 0; i < k; ++i) {
            S += a[idx[i]];
        }
    } else {
        // Pick a random target sum in the allowed range
        S = rnd.next(-1000000, 1000000);
    }
    // Output in the required format
    println(N, S);
    for (int i = 0; i < N; ++i) {
        printf("%d%c", a[i], (i + 1 == N ? '\n' : ' '));
    }
    return 0;
}
