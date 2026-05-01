#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 5);
    int N;
    vector<ll> A;
    if (type == 0) {
        // Very small N, small values
        N = rnd.next(1, 3);
        A.resize(N);
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1, 10);
    } else if (type == 1) {
        // Distinct moderate N, moderate range
        N = rnd.next(4, 12);
        set<ll> s;
        while ((int)s.size() < N)
            s.insert(rnd.next(1, 100));
        A.assign(s.begin(), s.end());
    } else if (type == 2) {
        // Many equal, with one low and one high outlier
        N = rnd.next(4, 12);
        int v = rnd.next(10, 50);
        A.assign(N, v);
        int p1 = rnd.next(0, N - 1), p2;
        do { p2 = rnd.next(0, N - 1); } while (p2 == p1);
        int low = (v > 1 ? rnd.next(1, v - 1) : 1);
        int high = rnd.next(v + 1, 100);
        A[p1] = low;
        A[p2] = high;
    } else if (type == 3) {
        // Random wide range
        N = rnd.next(4, 12);
        A.resize(N);
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1, 1000);
    } else if (type == 4) {
        // Skew: mostly small, one large
        N = rnd.next(4, 12);
        A.resize(N - 1);
        for (int i = 0; i < N - 1; i++)
            A[i] = rnd.next(1, 20);
        A.push_back(rnd.next(500, 1000));
    } else {
        // Skew: mostly large, one small
        N = rnd.next(4, 12);
        A.resize(N - 1);
        for (int i = 0; i < N - 1; i++)
            A[i] = rnd.next(500, 1000);
        A.push_back(rnd.next(1, 20));
    }
    shuffle(A.begin(), A.end());
    println(N);
    println(A);
    return 0;
}
