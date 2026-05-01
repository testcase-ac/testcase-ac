#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter choices for weights
    vector<int> ts = {-2, -1, 0, 1, 2};
    // Length bias parameter
    int tLen = rnd.any(ts);
    int N = rnd.wnext(30, tLen) + 1; // N in [1,31]

    // Bias for player 1 (minimizer) and player 2 (maximizer)
    int t1 = rnd.any(ts);
    int t2 = rnd.any(ts);

    string s1, s2;
    s1.reserve(N);
    s2.reserve(N);
    for (int i = 0; i < N; i++) {
        int c1 = rnd.wnext(26, t1); // 0..25
        int c2 = rnd.wnext(26, t2);
        s1.push_back(char('a' + c1));
        s2.push_back(char('a' + c2));
    }

    println(s1);
    println(s2);

    return 0;
}
