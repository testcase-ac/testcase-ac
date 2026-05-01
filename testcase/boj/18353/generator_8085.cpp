#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with varied sizes: very small, small, medium, larger (but ≤30)
    double pr = rnd.next();
    int N;
    if (pr < 0.1)      N = rnd.next(1, 3);
    else if (pr < 0.3) N = rnd.next(4, 10);
    else if (pr < 0.8) N = rnd.next(11, 25);
    else               N = rnd.next(26, 30);

    vector<int> a(N);
    // Choose pattern mode for diversity
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        // Mostly strictly decreasing (with slight randomness)
        int cur = rnd.next(N, N * 1000);
        for (int i = 0; i < N; i++) {
            a[i] = cur;
            cur -= rnd.next(1, 10);
            if (cur < 1) cur = 1;
        }
    }
    else if (mode == 1) {
        // Mostly strictly increasing
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < N; i++) {
            a[i] = cur;
            cur += rnd.next(1, 10);
        }
    }
    else if (mode == 2) {
        // Fully random values
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, 10000000);
        }
    }
    else if (mode == 3) {
        // Plateaus: a few segments of equal values
        int seg = rnd.next(1, min(N, 5));
        int rem = seg, idx = 0;
        while (rem > 1) {
            int maxLen = N - idx - (rem - 1);
            int len = rnd.next(1, maxLen);
            int val = rnd.next(1, 1000);
            for (int j = 0; j < len; j++) {
                a[idx++] = val;
            }
            rem--;
        }
        int val = rnd.next(1, 1000);
        while (idx < N) {
            a[idx++] = val;
        }
    }
    else if (mode == 4) {
        // Mountain: increasing then decreasing
        int peak = rnd.next(0, N - 1);
        int cur = rnd.next(1, 1000);
        for (int i = 0; i <= peak; i++) {
            a[i] = cur;
            cur += rnd.next(1, 10);
        }
        int down = cur;
        for (int i = peak + 1; i < N; i++) {
            down -= rnd.next(1, 10);
            if (down < 1) down = 1;
            a[i] = down;
        }
    }
    else {
        // Valley: decreasing then increasing
        int trough = rnd.next(0, N - 1);
        int cur = rnd.next(N, N * 1000);
        for (int i = 0; i <= trough; i++) {
            a[i] = cur;
            cur -= rnd.next(1, 10);
            if (cur < 1) cur = 1;
        }
        int up = cur;
        for (int i = trough + 1; i < N; i++) {
            up += rnd.next(1, 10);
            a[i] = up;
        }
    }

    // Output the test case
    println(N);
    println(a);

    return 0;
}
