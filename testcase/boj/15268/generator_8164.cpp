#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n: mostly small, sometimes medium for variability
    int n;
    if (rnd.next(9) == 0) {
        // medium size
        n = rnd.next(16, 50);
    } else {
        // small size (including possible n=1)
        n = rnd.next(1, 15);
    }

    // Choose pattern for required shifts d[i] in [0,6]
    int pat = rnd.next(2);
    vector<int> d(n);
    if (pat == 0) {
        // fully random shifts
        for (int i = 0; i < n; i++) {
            d[i] = rnd.next(0, 6);
        }
    } else if (pat == 1) {
        // contiguous segments with same shift
        int i = 0;
        while (i < n) {
            int rem = n - i;
            int len = rnd.next(1, min(rem, 5));
            int di = rnd.next(0, 6);
            for (int j = 0; j < len; j++) {
                d[i + j] = di;
            }
            i += len;
        }
    } else {
        // cyclic pattern of shifts
        for (int i = 0; i < n; i++) {
            d[i] = i % 7;
        }
    }

    // Build each initial knob string s[i], ensuring the maximal rotation is unique
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        // Generate a maximal string mx of length 7 with a unique largest digit
        string mx(7, '1');
        int dmax = rnd.next(2, 9);
        int posMax = rnd.next(0, 6);
        for (int j = 0; j < 7; j++) {
            if (j == posMax) {
                mx[j] = char('0' + dmax);
            } else {
                mx[j] = char('0' + rnd.next(1, dmax - 1));
            }
        }
        // Compute initial string by rotating mx so that rotating by d[i] yields mx
        int shiftLeft = (7 - d[i]) % 7;  // rotate left by shiftLeft
        string t1 = mx.substr(shiftLeft);
        string t2 = mx.substr(0, shiftLeft);
        s[i] = t1 + t2;
    }

    // Output
    println(n);
    for (int i = 0; i < n; i++) {
        printf("%s\n", s[i].c_str());
    }

    return 0;
}
