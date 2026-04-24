#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = (1<<24) - 1; // 24-bit max
    int n = rnd.next(1, 10);

    vector<int> vals;
    if (n >= 2) {
        // always include the extremes
        vals.push_back(1);
        vals.push_back(MAXV);
        for (int i = 2; i < n; i++) {
            int cat = rnd.next(0, 2);
            int v;
            if (cat == 0) {
                // bias towards small numbers
                v = rnd.wnext(MAXV+1, -2);
            } else if (cat == 1) {
                // bias towards large numbers
                v = rnd.wnext(MAXV+1, 2);
            } else {
                // uniform
                v = rnd.next(1, MAXV);
            }
            if (v == 0) v = 1;
            vals.push_back(v);
        }
    } else {
        // single test case: pick one extreme
        int v = (rnd.next(0, 1) == 0 ? 1 : MAXV);
        vals.push_back(v);
    }

    // shuffle to mix positions
    shuffle(vals.begin(), vals.end());

    // output
    println(n);
    for (int v : vals) {
        string s(24, '0');
        for (int i = 0; i < 24; i++) {
            if (v & (1 << (23 - i))) s[i] = '1';
        }
        println(s);
    }

    return 0;
}
