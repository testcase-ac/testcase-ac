#include "testlib.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N small
    int N = rnd.next(1, 10);
    // Mode selection for diverse patterns
    int mode = rnd.next(0, 4);
    vector<int> P(N + 1);
    if (mode == 0) {
        // Increasing sequence
        int cur = rnd.next(1, 5);
        for (int i = 1; i <= N; i++) {
            cur += rnd.next(0, 5);
            P[i] = cur;
        }
    } else if (mode == 1) {
        // Decreasing sequence
        int cur = rnd.next(1, 5) + N * 5;
        for (int i = 1; i <= N; i++) {
            cur -= rnd.next(0, 5);
            if (cur < 1) cur = 1;
            P[i] = cur;
        }
    } else if (mode == 2) {
        // Completely random
        for (int i = 1; i <= N; i++) {
            P[i] = rnd.next(1, 20);
        }
    } else if (mode == 3) {
        // Fibonacci-like with noise
        if (N >= 1) P[1] = rnd.next(1, 10);
        if (N >= 2) P[2] = rnd.next(1, 10);
        for (int i = 3; i <= N; i++) {
            int noise = rnd.next(0, 6) - 3; // [-3,3]
            int val = P[i-1] + P[i-2] + noise;
            P[i] = max(1, val);
        }
    } else {
        // Random with a local spike
        for (int i = 1; i <= N; i++) {
            P[i] = rnd.next(1, 15);
        }
        int spike_pos = rnd.next(1, N);
        int mx = *max_element(P.begin()+1, P.begin()+N+1);
        P[spike_pos] = mx + rnd.next(5, 15);
    }
    // Output
    println(N);
    vector<int> out(N);
    for (int i = 1; i <= N; i++) out[i-1] = P[i];
    println(out);
    return 0;
}
