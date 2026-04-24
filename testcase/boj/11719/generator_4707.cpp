#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of lines: small, up to 10
    int L = rnd.next(1, 10);
    // maximum line length hyper-parameter
    int maxLen = rnd.next(0, 20);
    // bias for line lengths: -1 small, 0 uniform, +1 towards max
    vector<int> biases = {-1, 0, 1};
    int lengthBias = rnd.any(biases);
    // character set: lowercase, uppercase, digits, space
    string chars = "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "0123456789 ";
    vector<string> lines;
    for (int i = 0; i < L; i++) {
        // generate length with possible bias
        int len = rnd.wnext(maxLen + 1, lengthBias);
        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            s += rnd.any(chars);
        }
        lines.push_back(s);
    }
    // output exactly as input
    for (auto &s : lines) {
        // preserve empty and space-prefixed/suffixed lines
        printf("%s\n", s.c_str());
    }
    return 0;
}
