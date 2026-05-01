#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases between 4 and 6
    int T = rnd.next(4, 6);
    println(T);
    for (int i = 0; i < T; i++) {
        int N;
        if (i == 0)      N = 1;
        else if (i == 1) N = 2;
        else if (i == 2) N = 3;
        else             N = rnd.next(1, 6);
        // build the standard folding sequence of length 2^N-1
        string s = "0";
        for (int j = 2; j <= N; j++) {
            string t = s;
            reverse(t.begin(), t.end());
            string comp;
            comp.reserve(t.size());
            for (char c : t) comp.push_back(c == '0' ? '1' : '0');
            s = s + '1' + comp;
        }
        bool makeValid;
        if (i < 4) {
            // force alternating valid/invalid for first 4
            makeValid = (i % 2 == 0);
        } else {
            makeValid = rnd.next(0, 1) == 1;
        }
        string out;
        if (makeValid) {
            // either original or fully reversed
            if (rnd.next(0, 1) == 0) {
                out = s;
            } else {
                out = s;
                reverse(out.begin(), out.end());
            }
        } else {
            // take s (or its reverse) and flip one random bit
            out = (rnd.next(0,1) == 0 ? s : string(s.rbegin(), s.rend()));
            int pos = rnd.next(0, (int)out.size() - 1);
            out[pos] = (out[pos] == '0' ? '1' : '0');
        }
        // print the test string
        printf("%s\n", out.c_str());
    }
    return 0;
}
