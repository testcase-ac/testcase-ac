#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    // Generate initial digits with some patterns
    vector<int> digits(N);
    double p0 = rnd.next();
    if (p0 < 0.1) {
        // all same
        int d = rnd.next(0, 9);
        for (int i = 0; i < N; i++) digits[i] = d;
    } else if (p0 < 0.3) {
        // monotonic inc or dec
        bool inc = rnd.next() < 0.5;
        int start = rnd.next(0, 9);
        for (int i = 0; i < N; i++) {
            if (inc) digits[i] = (start + i) % 10;
            else digits[i] = (start - i % 10 + 10) % 10;
        }
    } else {
        // random
        for (int i = 0; i < N; i++)
            digits[i] = rnd.next(0, 9);
    }
    // Build digit string
    string s;
    for (int d : digits) s.push_back(char('0' + d));
    // Generate queries
    vector<pair<int,int>> qs;
    for (int i = 0; i < M; i++) {
        double p = rnd.next();
        int A, B;
        if (p < 0.15) {
            // single
            A = rnd.next(1, N);
            B = A;
        } else if (p < 0.35) {
            // full range
            A = 1; B = N;
        } else if (p < 0.6) {
            // small range
            A = rnd.next(1, N);
            int maxLen = max(1, N/3);
            int len = rnd.next(1, maxLen);
            B = min(N, A + len - 1);
        } else {
            // random
            A = rnd.next(1, N);
            B = rnd.next(A, N);
        }
        qs.emplace_back(A, B);
    }
    // Output
    println(N, M);
    printf("%s\n", s.c_str());
    for (auto &q : qs) println(q.first, q.second);
    return 0;
}
