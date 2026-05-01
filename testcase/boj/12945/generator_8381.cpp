#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(1, 15);
    vector<int> maxOpts = {10, 100, 1000, 100000};
    int maxV = rnd.any(maxOpts);
    int dtype = rnd.next(0, 3);

    vector<int> V(N);
    if (dtype == 0) {
        // Uniform random
        for (int i = 0; i < N; i++)
            V[i] = rnd.next(1, maxV);
    } else if (dtype == 1) {
        // Powers of two
        int maxPow = floor(log2(maxV));
        for (int i = 0; i < N; i++) {
            int k = rnd.next(0, maxPow);
            V[i] = 1 << k;
        }
    } else if (dtype == 2) {
        // Clustered around a few centers
        int c = rnd.next(1, min(N, 3));
        vector<int> centers(c);
        for (int j = 0; j < c; j++)
            centers[j] = rnd.next(1, maxV);
        for (int i = 0; i < N; i++) {
            int j = rnd.next(0, c - 1);
            int delta = max(1, centers[j] / 10);
            int off = rnd.next(-delta, delta);
            int v = centers[j] + off;
            V[i] = min(max(v, 1), maxV);
        }
    } else {
        // Nearly sorted sequence
        V[0] = rnd.next(1, maxV);
        for (int i = 1; i < N; i++) {
            int rem = maxV - V[i - 1];
            int delta = 0;
            if (rem > 0) delta = rnd.next(0, rem / (N - i));
            V[i] = V[i - 1] + delta;
        }
        if (rnd.next(0, 1) == 1)
            reverse(V.begin(), V.end());
    }

    if (dtype != 3)
        shuffle(V.begin(), V.end());

    println(N);
    for (int x : V) println(x);

    return 0;
}
