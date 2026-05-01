#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of shares N
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0)       N = rnd.next(1, 3);
    else if (mode == 1)  N = rnd.next(4, 10);
    else                 N = rnd.next(11, 30);

    // Choose generation pattern
    int pattern = rnd.next(0, 3);
    // pattern 3 (zero-heavy valid) requires at least 2 shares
    if (pattern == 3 && N < 2) pattern = rnd.next(0, 2);

    vector<string> shares;
    shares.reserve(N);

    if (pattern == 1) {
        // INVALID case: all shares are zeros-only
        for (int i = 0; i < N; i++) {
            int len = rnd.next(1, 5);
            shares.push_back(string(len, '0'));
        }
    }
    else if (pattern == 0) {
        // Uniform random shares, ensure at least one non-zero start
        bool hasNonZero = false;
        for (int i = 0; i < N; i++) {
            int len = rnd.next(1, 5);
            string s;
            for (int j = 0; j < len; j++) {
                char c = char('0' + rnd.next(0, 9));
                s.push_back(c);
                if (j == 0 && c != '0') hasNonZero = true;
            }
            shares.push_back(s);
        }
        if (!hasNonZero) {
            int idx = rnd.next(0, N - 1);
            shares[idx][0] = char('1' + rnd.next(0, 8));
        }
    }
    else if (pattern == 2) {
        // Prefix cluster to catch incorrect sorting
        int pcount = rnd.next(1, min(3, N));
        vector<string> bases;
        for (int k = 0; k < pcount; k++) {
            int blen = rnd.next(1, 3);
            string b;
            b.push_back(char('1' + rnd.next(0, 8))); // non-zero start
            for (int j = 1; j < blen; j++)
                b.push_back(char('0' + rnd.next(0, 9)));
            bases.push_back(b);
        }
        for (int i = 0; i < N; i++) {
            string b = rnd.any(bases);
            int maxExt = 5 - (int)b.size();
            int ext = rnd.next(0, maxExt);
            string s = b;
            for (int e = 0; e < ext; e++)
                s.push_back(b[e % b.size()]);
            shares.push_back(s);
        }
    }
    else {
        // Zero-heavy but valid: some all-zero shares, some random non-zero-start
        int zeroCount = rnd.next(1, N - 1);
        for (int i = 0; i < zeroCount; i++) {
            int len = rnd.next(1, 5);
            shares.push_back(string(len, '0'));
        }
        for (int i = zeroCount; i < N; i++) {
            int len = rnd.next(1, 5);
            string s;
            for (int j = 0; j < len; j++)
                s.push_back(char('0' + rnd.next(0, 9)));
            if (s[0] == '0')
                s[0] = char('1' + rnd.next(0, 8));
            shares.push_back(s);
        }
    }

    // Shuffle shares to avoid any generation order bias
    shuffle(shares.begin(), shares.end());

    // Output
    println(N);
    println(shares);

    return 0;
}
