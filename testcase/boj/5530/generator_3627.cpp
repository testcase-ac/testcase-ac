#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size
    int N = rnd.next(1, 20);
    int mode = rnd.next(0, 3);
    string s;
    const string alph = "JOI";

    if (mode == 0) {
        // Uniform random
        for (int i = 0; i < N; i++) {
            s += rnd.any(alph);
        }
    }
    else if (mode == 1) {
        // Skewed distribution: one heavy character
        char heavy = rnd.any(alph);
        double p = rnd.next(5, 8) / 10.0; // between 0.5 and 0.8
        vector<char> others;
        for (char c : alph)
            if (c != heavy) others.push_back(c);
        for (int i = 0; i < N; i++) {
            if (rnd.next() < p) s += heavy;
            else s += rnd.any(others);
        }
    }
    else if (mode == 2) {
        // Blocky segments
        int seg = rnd.next(1, min(N, 5));
        int rem = N;
        for (int j = 1; j <= seg; j++) {
            int len;
            if (j == seg) {
                len = rem;
            } else {
                // leave at least 1 for each future segment
                len = rnd.next(1, rem - (seg - j));
            }
            rem -= len;
            char c = rnd.any(alph);
            s.append(len, c);
        }
    }
    else {
        // Patterned with noise
        vector<string> pats = {"JOI", "IOI"};
        string pat = rnd.any(pats);
        while ((int)s.size() < N) {
            s += pat;
        }
        if ((int)s.size() > N) s.resize(N);
        int flips = rnd.next(0, N/5);
        for (int k = 0; k < flips; k++) {
            int idx = rnd.next(0, N-1);
            s[idx] = rnd.any(alph);
        }
    }

    println(N);
    println(s);

    return 0;
}
