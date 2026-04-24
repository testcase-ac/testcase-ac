#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkable cases
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    vector<char> alpha = {'A', 'C', 'G', 'T'};
    string s, t;
    s.reserve(N);
    t.reserve(M);

    // Hyper-parameter: sometimes embed part of S into T
    if (rnd.next() < 0.3 && N > 1) {
        for (int i = 0; i < N; i++)
            s.push_back(rnd.any(alpha));
        int len = min(N, M);
        int start = rnd.next(0, N - len);
        string sub = s.substr(start, len);
        int pre = rnd.next(0, M);
        int suf = M - pre - len;
        if (suf < 0) suf = 0;
        for (int i = 0; i < pre; i++) t.push_back(rnd.any(alpha));
        t += sub;
        for (int i = 0; i < suf; i++) t.push_back(rnd.any(alpha));
        while ((int)t.size() < M) t.push_back(rnd.any(alpha));
        if ((int)t.size() > M) t.resize(M);
    } else {
        for (int i = 0; i < N; i++)
            s.push_back(rnd.any(alpha));
        for (int i = 0; i < M; i++)
            t.push_back(rnd.any(alpha));
    }

    // Costs for inserting A, C, G, T
    int costA = rnd.next(0, 20);
    int costC = rnd.next(0, 20);
    int costG = rnd.next(0, 20);
    int costT = rnd.next(0, 20);

    // Output
    printf("%s\n", s.c_str());
    printf("%s\n", t.c_str());
    println(costA, costC, costG, costT);

    return 0;
}
