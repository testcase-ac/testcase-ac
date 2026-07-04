#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(7);
        int n;
        int d;

        if (mode == 0) {
            n = rnd.next(1, 8);
            d = 2;
        } else if (mode <= 2) {
            n = rnd.next(2, 18);
            d = rnd.next(2, 10);
        } else if (mode == 3) {
            n = rnd.next(20, 45);
            d = rnd.next(2, 10);
        } else {
            n = rnd.next(3, 28);
            d = rnd.next(11, 1000000000);
        }

        vector<int> v(n);
        if (mode == 0) {
            int bit = rnd.next(2);
            for (int i = 0; i < n; ++i) {
                v[i] = (bit + i) % 2;
            }
        } else if (mode == 1) {
            int runValue = rnd.next(0, d - 1);
            for (int i = 0; i < n; ++i) {
                if (i == 0 || rnd.next(100) < 30) {
                    runValue = rnd.next(0, d - 1);
                }
                v[i] = runValue;
            }
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                v[i] = (i % 3 == 0) ? 0 : rnd.next(0, d - 1);
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                v[i] = rnd.next(0, d - 1);
            }
        } else if (mode == 4) {
            vector<int> choices = {0, 1, d - 1};
            for (int i = 0; i < n; ++i) {
                v[i] = rnd.any(choices);
            }
        } else if (mode == 5) {
            int step = rnd.next(1, min(d - 1, 25));
            int cur = rnd.next(0, d - 1);
            for (int i = 0; i < n; ++i) {
                v[i] = cur;
                cur = (cur + step) % d;
            }
        } else {
            for (int i = 0; i < n; ++i) {
                if (i < n / 2) {
                    v[i] = rnd.next(0, min(d - 1, 3));
                } else {
                    v[i] = rnd.next(max(0, d - 4), d - 1);
                }
            }
            if (rnd.next(2)) {
                reverse(v.begin(), v.end());
            }
        }

        println(n, d);
        println(v);
    }

    return 0;
}
