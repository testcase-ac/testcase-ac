#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 6);
    int N = 1;

    // Decide N based on type to hit various edge regions
    if (type == 0) { // no deletions, boundary-focused
        int sub = rnd.next(0, 4);
        if (sub == 0)      N = rnd.next(1, 9);      // very small
        else if (sub == 1) N = rnd.next(8, 12);     // around 9-10
        else if (sub == 2) N = rnd.next(95, 105);   // around 99-100
        else if (sub == 3) N = rnd.next(180, 200);  // near upper limit
        else               N = rnd.next(1, 200);    // general
    } else if (type == 2) { // zeros-heavy
        N = rnd.next(50, 200);
    } else if (type == 3) { // digit-run
        N = rnd.next(20, 200);
    } else {
        N = rnd.next(1, 200);
    }

    // Build concatenated string T = "123...N"
    string T;
    T.reserve(500);
    for (int i = 1; i <= N; ++i) {
        T += to_string(i);
    }
    int L = (int)T.size();

    vector<char> keep(L, 0);

    if (type == 0) {
        // No deletions: keep everything
        fill(keep.begin(), keep.end(), 1);
    } else if (type == 1) {
        // Random deletions with a chosen density
        double probs[] = {0.25, 0.5, 0.75};
        double p = probs[rnd.next(0, 2)];
        for (int i = 0; i < L; ++i) {
            if (rnd.next() < p) keep[i] = 1;
        }
    } else if (type == 2) {
        // Keep only zeros (possibly some subset)
        double probs[] = {0.4, 0.7, 1.0};
        double p = probs[rnd.next(0, 2)];
        for (int i = 0; i < L; ++i) {
            if (T[i] == '0' && rnd.next() < p) keep[i] = 1;
        }
    } else if (type == 3) {
        // Keep only a chosen digit
        char d = char('0' + rnd.next(0, 9));
        double probs[] = {0.3, 0.6, 1.0};
        double p = probs[rnd.next(0, 2)];
        for (int i = 0; i < L; ++i) {
            if (T[i] == d && rnd.next() < p) keep[i] = 1;
        }
    } else if (type == 4) {
        // Single contiguous substring
        int l = rnd.next(0, L - 1);
        int r = rnd.next(l, L - 1);
        for (int i = l; i <= r; ++i) keep[i] = 1;
    } else if (type == 5) {
        // Two disjoint contiguous substrings (if possible)
        if (L == 1) {
            keep[0] = 1;
        } else {
            int l1 = rnd.next(0, L - 2);
            int r1 = rnd.next(l1, L - 2);
            int l2 = rnd.next(r1 + 1, L - 1);
            int r2 = rnd.next(l2, L - 1);
            for (int i = l1; i <= r1; ++i) keep[i] = 1;
            for (int i = l2; i <= r2; ++i) keep[i] = 1;
        }
    } else if (type == 6) {
        // Very sparse: keep a few random positions
        int K = rnd.next(1, min(10, L));
        for (int t = 0; t < K; ++t) {
            int pos = rnd.next(0, L - 1);
            keep[pos] = 1;
        }
    }

    // Ensure at least one digit is kept
    int cnt = 0;
    for (int i = 0; i < L; ++i) if (keep[i]) ++cnt;
    if (cnt == 0) {
        int j = rnd.next(0, L - 1);
        keep[j] = 1;
    }

    // Build the resulting subsequence S
    string S;
    S.reserve(L);
    for (int i = 0; i < L; ++i) {
        if (keep[i]) S.push_back(T[i]);
    }

    println(S);
    return 0;
}
