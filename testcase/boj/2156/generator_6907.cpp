#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide on small or medium size to catch edge and general cases
    bool small = rnd.next(0, 1);
    int n = small ? rnd.next(1, 5) : rnd.next(6, 15);

    vector<int> a(n);
    // Choose a pattern type for variability
    int pat = rnd.next(0, 5);
    switch (pat) {
        case 0:
            // fully random values
            for (int i = 0; i < n; i++)
                a[i] = rnd.next(0, 1000);
            break;
        case 1:
            // mostly zeros, some small values
            for (int i = 0; i < n; i++) {
                if (rnd.next(0, 9) < 7)
                    a[i] = 0;
                else
                    a[i] = rnd.next(1, 100);
            }
            break;
        case 2: {
            // increasing sequence
            int cur = rnd.next(0, 100);
            for (int i = 0; i < n; i++) {
                cur += rnd.next(0, 50);
                a[i] = min(cur, 1000);
            }
            break;
        }
        case 3:
            // alternating high and low
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0)
                    a[i] = rnd.next(800, 1000);
                else
                    a[i] = rnd.next(0, 200);
            }
            break;
        case 4: {
            // plateaus of constant values
            int i = 0;
            while (i < n) {
                int len = rnd.next(1, min(n - i, 3));
                int val = rnd.next(0, 1000);
                for (int j = 0; j < len; j++)
                    a[i + j] = val;
                i += len;
            }
            break;
        }
        case 5: {
            // decreasing sequence
            int cur = rnd.next(0, 1000);
            for (int i = 0; i < n; i++) {
                cur -= rnd.next(0, 50);
                if (cur < 0) cur = 0;
                a[i] = cur;
            }
            break;
        }
    }

    // Output
    println(n);
    for (int x : a) println(x);
    return 0;
}
