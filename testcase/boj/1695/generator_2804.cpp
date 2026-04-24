#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int variant = rnd.next(0, 3);
    int low = rnd.next(-5, 5);
    int high = rnd.next(low, low + 5);

    vector<int> a;
    int N;

    if (variant == 0) {
        // Completely random sequence
        N = rnd.next(1, 10);
        a.resize(N);
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(low, high);
        }
    } else if (variant == 1) {
        // Exact palindrome
        N = rnd.next(1, 10);
        vector<int> half((N + 1) / 2);
        for (int i = 0; i < (int)half.size(); i++) {
            half[i] = rnd.next(low, high);
        }
        a = half;
        for (int i = N / 2 - 1; i >= 0; i--) {
            a.push_back(half[i]);
        }
    } else if (variant == 2) {
        // Near-palindrome by removal: create palindrome of length M, remove k to produce N
        int M = rnd.next(2, 10);
        int k = rnd.next(1, M - 1);
        N = M - k;
        // build palindrome c of length M
        vector<int> c;
        vector<int> half((M + 1) / 2);
        for (int i = 0; i < (int)half.size(); i++) {
            half[i] = rnd.next(low, high);
        }
        c = half;
        for (int i = M / 2 - 1; i >= 0; i--) {
            c.push_back(half[i]);
        }
        // choose k distinct positions to remove
        vector<int> idx(M);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        vector<bool> to_remove(M, false);
        for (int i = 0; i < k; i++) {
            to_remove[idx[i]] = true;
        }
        // build a
        for (int i = 0; i < M; i++) {
            if (!to_remove[i]) a.push_back(c[i]);
        }
    } else {
        // Constant sequence
        N = rnd.next(1, 10);
        int v = rnd.next(low, high);
        a.assign(N, v);
    }

    // Output result
    println(N);
    println(a);

    return 0;
}
