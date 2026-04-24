#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // length of string S
    int N = rnd.next(1, 10);
    // alphabet size (chars from 'a' to 'a'+alph_size-1)
    int alph_size = rnd.next(1, 5);
    vector<char> alph;
    for (int i = 0; i < alph_size; i++)
        alph.push_back(char('a' + i));

    // build string S, sometimes with a small repeating pattern
    string s;
    s.resize(N);
    if (rnd.next() < 0.4) {
        int patLen = rnd.next(1, min(N, 3));
        vector<char> pat(patLen);
        for (int i = 0; i < patLen; i++)
            pat[i] = rnd.any(alph);
        for (int i = 0; i < N; i++)
            s[i] = pat[i % patLen];
    } else {
        for (int i = 0; i < N; i++)
            s[i] = rnd.any(alph);
    }

    // total number of substrings
    int tot = N * (N + 1) / 2;
    // decide whether to overshoot K or pick within range
    bool overshoot = rnd.next() < 0.3;
    int K;
    if (overshoot) {
        // allow some invalid K > tot
        int hi = min(100000, tot * 2);
        if (hi < tot + 1) hi = tot + 1;
        K = rnd.next(tot + 1, hi);
    } else {
        K = rnd.next(1, tot);
    }

    // output
    printf("%s\n", s.c_str());
    println(K);

    return 0;
}
