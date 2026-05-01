#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 30);
    int maxA = rnd.next(5, 100);
    int type = rnd.next(0, 6);
    vector<int> a(N);
    switch (type) {
        case 0: { // strictly increasing
            int start = rnd.next(1, max(1, maxA - N));
            int step = rnd.next(1, max(1, (maxA - start) / N));
            for (int i = 0; i < N; i++) a[i] = start + step * i;
            break;
        }
        case 1: { // strictly decreasing
            int start = rnd.next(N, N + maxA);
            int step = rnd.next(1, max(1, (start - 1) / N));
            for (int i = 0; i < N; i++) a[i] = start - step * i;
            break;
        }
        case 2: { // all equal
            int v = rnd.next(1, maxA);
            for (int i = 0; i < N; i++) a[i] = v;
            break;
        }
        case 3: { // valley at start
            int v0 = rnd.next(1, min(10, maxA - 1));
            a[0] = v0;
            for (int i = 1; i < N; i++) a[i] = rnd.next(v0 + 1, maxA);
            break;
        }
        case 4: { // peak at end
            for (int i = 0; i < N - 1; i++) a[i] = rnd.next(1, maxA);
            int mx = *max_element(a.begin(), a.begin() + max(1, N - 1));
            a[N - 1] = mx + rnd.next(1, 10);
            break;
        }
        case 5: { // zigzag pattern
            int low = rnd.next(1, maxA / 2);
            int high = rnd.next(low + 1, maxA);
            for (int i = 0; i < N; i++) {
                int diff = high - low - 1;
                int delta = diff > 0 ? rnd.next(0, min(5, diff)) : 0;
                if (i % 2 == 0) a[i] = low + delta;
                else a[i] = high - delta;
            }
            break;
        }
        case 6: default: { // fully random
            for (int i = 0; i < N; i++) a[i] = rnd.next(1, maxA);
            break;
        }
    }
    println(N);
    println(a);
    return 0;
}
