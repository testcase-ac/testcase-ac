#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int dist = rnd.next(1, 6);
    int N;
    vector<int> X;
    int K;
    if (dist == 1) {
        // Single character case
        N = 1;
        X.resize(1);
        X[0] = rnd.next(1, 1000);
        K = rnd.next(1, 100);
    } else {
        N = rnd.next(2, 10);
        X.resize(N);
        if (dist == 2) {
            // All levels equal
            int v = rnd.next(1, 100);
            for (int i = 0; i < N; i++) X[i] = v;
            K = rnd.next(1, N * 100);
        } else if (dist == 3) {
            // Uniform random small levels
            for (int i = 0; i < N; i++) X[i] = rnd.next(1, 100);
            K = rnd.next(1, N * 100);
        } else if (dist == 4) {
            // One high outlier, others small
            for (int i = 0; i < N - 1; i++) X[i] = rnd.next(1, 50);
            X[N - 1] = rnd.next(100, 1000);
            K = rnd.next(1, (N - 1) * 50);
        } else if (dist == 5) {
            // Large K to allow overshooting max
            for (int i = 0; i < N; i++) X[i] = rnd.next(1, 50);
            K = rnd.next(N * 50, N * 200);
        } else {
            // One extremely large level, rest moderate
            X[0] = 1000000000;
            for (int i = 1; i < N; i++) X[i] = rnd.next(1, 100);
            K = rnd.next(1, N * 100);
        }
    }
    shuffle(X.begin(), X.end());
    println(N, K);
    for (int v : X) println(v);
    return 0;
}
