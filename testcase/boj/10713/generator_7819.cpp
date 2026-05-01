#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for small, varied sizes
    int N = rnd.next(5, 12);
    int M = rnd.next(3, 12);

    // Generate travel plan P
    vector<int> P(M);
    P[0] = rnd.next(1, N);
    for (int j = 1; j < M; ++j) {
        if (rnd.next() < 0.5) {
            vector<int> nbr;
            if (P[j-1] > 1) nbr.push_back(P[j-1] - 1);
            if (P[j-1] < N) nbr.push_back(P[j-1] + 1);
            if (!nbr.empty()) {
                P[j] = rnd.any(nbr);
                continue;
            }
        }
        // pick a random city different from previous
        int x;
        do {
            x = rnd.next(1, N);
        } while (x == P[j-1]);
        P[j] = x;
    }

    // Count usage frequency for each railway segment
    vector<int> freq(N+1, 0);
    for (int j = 0; j + 1 < M; ++j) {
        int a = P[j], b = P[j+1];
        if (a > b) swap(a, b);
        for (int i = a; i < b; ++i) {
            freq[i]++;
        }
    }

    // Build A, B, C for each segment
    vector<array<int,3>> seg(N);
    for (int i = 1; i < N; ++i) {
        int k = freq[i];
        int B = rnd.next(1, 20);
        int d = rnd.next(1, 20);
        int A = B + d;
        // Decide relation of C to total benefit = k * d
        int benefit = k * d;
        int type = 0; // 0: C > benefit, 1: C == benefit, 2: C < benefit
        if (k > 0) {
            type = rnd.next(0, 2);
            if (type == 1 && benefit < 1) type = 0;
            if (type == 2 && benefit < 2) type = 0;
        }
        int C;
        if (type == 1) {
            C = benefit;
        } else if (type == 2) {
            C = rnd.next(1, benefit - 1);
        } else {
            // ensure C > benefit
            int low = benefit + 1;
            int high = benefit + 1 + rnd.next(1, 20);
            C = rnd.next(low, high);
        }
        seg[i] = {A, B, C};
    }

    // Output
    println(N, M);
    println(P);
    for (int i = 1; i < N; ++i) {
        println(seg[i][0], seg[i][1], seg[i][2]);
    }
    return 0;
}
