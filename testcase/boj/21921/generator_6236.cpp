#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 2 and 20 with some bias
    int bias = rnd.next(-2, 2);
    int N = rnd.wnext(19, bias) + 2;  // yields [2,20]
    int X = rnd.next(1, N);

    vector<int> a(N, 0);
    int scen = rnd.next(1, 5);
    if (scen == 1) {
        // Fully random
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(0, 8000);
        }
    } else if (scen == 2) {
        // Mostly zeros, occasional random
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.8)
                a[i] = 0;
            else
                a[i] = rnd.next(1, 8000);
        }
    } else if (scen == 3) {
        // Increasing trend with noise
        int start = rnd.next(0, 1000);
        int inc = rnd.next(0, 100);
        for (int i = 0; i < N; i++) {
            int val = start + inc * i + rnd.next(-inc/2, inc/2);
            if (val < 0) val = 0;
            if (val > 8000) val = 8000;
            a[i] = val;
        }
    } else if (scen == 4) {
        // Periodic peaks
        int P = rnd.next(1, min(3, N));
        for (int p = 0; p < P; p++) {
            int pos = rnd.next(0, N - 1);
            int h = rnd.next(1000, 8000);
            for (int j = pos; j < N && j < pos + X; j++) {
                a[j] = max(a[j], h);
            }
        }
        // fill remaining with small random
        for (int i = 0; i < N; i++)
            if (a[i] == 0)
                a[i] = rnd.next(0, 500);
    } else {
        // All zeros (to test SAD)
        // vector already zero-initialized
    }

    // Output
    println(N, X);
    println(a);
    return 0;
}
