#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string token = inf.readToken("0|[1-9A-Fa-f][0-9A-Fa-f]?", "cipher_i");
        int val = 0;
        for (char c : token) {
            val *= 16;
            if (c >= '0' && c <= '9') {
                val += c - '0';
            } else if (c >= 'A' && c <= 'F') {
                val += c - 'A' + 10;
            } else {
                val += c - 'a' + 10;
            }
        }

        ensuref(val <= 127, "cipher_%d parsed value %d not in [0,127]", i + 1, val);
        if (i + 1 < n) {
            inf.readSpace();
        }
    }

    inf.readEoln();
    inf.readEof();
    return 0;
}
