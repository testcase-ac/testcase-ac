#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(6, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int type = rnd.next(0, 4);
        int N;
        string S;
        if (type == 0) {
            // small random
            N = rnd.next(3, 5);
            for (int i = 0; i < N; i++)
                S += (rnd.next(0, 1) ? 'H' : 'T');
        } else if (type == 1) {
            // N = 1 or 2 special cases
            vector<int> optsN = {1, 2};
            N = rnd.any(optsN);
            vector<string> opts;
            if (N == 1) {
                opts = {"H", "T"};
            } else {
                opts = {"HH", "HT", "TH", "TT"};
            }
            S = rnd.any(opts);
        } else if (type == 2) {
            // one block of even-length T
            N = rnd.next(4, 20);
            vector<int> evens;
            for (int e = 2; e <= N; e += 2) evens.push_back(e);
            int L = rnd.any(evens);
            int pos = rnd.next(0, N - L);
            S = string(N, 'H');
            for (int i = pos; i < pos + L; i++) S[i] = 'T';
        } else if (type == 3) {
            // alternating pattern
            N = rnd.next(3, 20);
            char start = rnd.next(0, 1) ? 'H' : 'T';
            for (int i = 0; i < N; i++) {
                if (i % 2 == 0) S += start;
                else S += (start == 'H' ? 'T' : 'H');
            }
        } else {
            // biased random
            N = rnd.next(5, 20);
            double p = rnd.next();
            for (int i = 0; i < N; i++) {
                S += (rnd.next() < p ? 'T' : 'H');
            }
        }

        // small chance to force impossible (odd T count)
        if (rnd.next(0, 9) == 0) {
            int cnt = 0;
            for (char c : S) if (c == 'T') cnt++;
            if (cnt % 2 == 0) {
                int idx = rnd.next(0, N - 1);
                S[idx] = 'T';
            }
        }

        println(N);
        printf("%s\n", S.c_str());
    }

    return 0;
}
