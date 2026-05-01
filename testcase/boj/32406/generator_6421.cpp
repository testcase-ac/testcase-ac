#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small to medium N for hand verification
    int N = rnd.next(2, 12);
    // Choose upper bound for values
    vector<int> ub = {10, 50, 100};
    int h = rnd.any(ub);
    // Choose pattern type
    int type = rnd.next(0, 4);
    vector<int> a(N), b(N);
    if (type == 0) {
        // Fully random
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, h);
            b[i] = rnd.next(1, h);
        }
    } else if (type == 1) {
        // Symmetric a == b
        for (int i = 0; i < N; i++) {
            int x = rnd.next(1, h);
            a[i] = b[i] = x;
        }
    } else if (type == 2) {
        // Ascending a, random b
        int step = max(1, h / max(1, N));
        int cur = rnd.next(1, step);
        int inc = max(1, h / max(1, 2 * N));
        for (int i = 0; i < N; i++) {
            if (i > 0) {
                cur += rnd.next(0, inc);
                if (cur > h) cur = h;
            }
            a[i] = cur;
            b[i] = rnd.next(1, h);
        }
    } else if (type == 3) {
        // Ascending b, random a
        int step = max(1, h / max(1, N));
        int cur = rnd.next(1, step);
        int inc = max(1, h / max(1, 2 * N));
        for (int i = 0; i < N; i++) {
            if (i > 0) {
                cur += rnd.next(0, inc);
                if (cur > h) cur = h;
            }
            b[i] = cur;
            a[i] = rnd.next(1, h);
        }
    } else {
        // Block pattern
        int K1 = rnd.next(1, N - 1);
        int K2 = rnd.next(1, N - 1);
        for (int i = 0; i < N; i++) {
            if (i < K1) a[i] = rnd.next(h/2+1, h);
            else       a[i] = rnd.next(1, max(1, h/2));
            if (i < K2) b[i] = rnd.next(h/2+1, h);
            else        b[i] = rnd.next(1, max(1, h/2));
        }
    }
    // Output
    println(N);
    println(a);
    println(b);
    return 0;
}
