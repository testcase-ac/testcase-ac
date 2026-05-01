#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of test cases
    int T = rnd.next(1, 10);
    println(T);

    // weights for length biasing
    vector<int> ws = {-2, -1, 0, 1, 2};

    for (int ti = 0; ti < T; ti++) {
        // pick a bias parameter to sample length in [1,30]
        int t = rnd.any(ws);
        int len = rnd.wnext(30, t) + 1;

        // decide palindrome or not (force palindrome if len==1)
        bool wantPal = rnd.next(0, 1) == 1;
        if (len < 2) wantPal = true;

        string s(len, 'A');
        int half = len / 2;
        // first build a palindrome
        for (int i = 0; i < half; i++) {
            char c = char(rnd.next('A', 'Z'));
            s[i] = c;
            s[len - 1 - i] = c;
        }
        if (len % 2 == 1) {
            s[half] = char(rnd.next('A', 'Z'));
        }

        if (!wantPal) {
            // introduce exactly one mismatch (avoid middle for odd length)
            int pos;
            do {
                pos = rnd.next(0, len - 1);
            } while (pos * 2 == len - 1);
            char orig = s[pos];
            char c;
            do { c = char(rnd.next('A', 'Z')); }
            while (c == orig);
            s[pos] = c;
        }

        println(s);
    }

    return 0;
}
