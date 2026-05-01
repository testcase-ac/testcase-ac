#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 9);

    int N = 0;
    vector<int> h;

    switch (mode) {
        case 0: {
            // Very small N (edge cases)
            N = rnd.next(1, 2);
            h.resize(N);
            if (N == 1) {
                h[0] = rnd.next(1, 20);
            } else {
                if (rnd.next(0, 1) == 0) {
                    int val = rnd.next(1, 20);
                    h[0] = val;
                    h[1] = val; // equal heights
                } else {
                    h[0] = rnd.next(1, 20);
                    h[1] = rnd.next(1, 20);
                }
            }
            break;
        }
        case 1: {
            // Small random
            N = rnd.next(3, 7);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 20);
            break;
        }
        case 2: {
            // Medium random
            N = rnd.next(8, 15);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 100000);
            break;
        }
        case 3: {
            // Larger (but still hand-checkable) random
            N = rnd.next(16, 40);
            h.resize(N);
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 100000);
            break;
        }
        case 4: {
            // Strictly increasing heights
            N = rnd.next(3, 20);
            h.resize(N);
            int cur = rnd.next(1, 20);
            h[0] = cur;
            for (int i = 1; i < N; ++i) {
                cur += rnd.next(1, 10);
                h[i] = cur;
            }
            break;
        }
        case 5: {
            // Strictly decreasing heights
            N = rnd.next(3, 20);
            h.resize(N);
            int start = rnd.next(3 * N, 3 * N + 40);
            int cur = start;
            for (int i = 0; i < N; ++i) {
                h[i] = cur;
                if (i + 1 < N)
                    cur -= rnd.next(1, 3);
            }
            // Guarantee minimum height at least 1
            for (int i = 0; i < N; ++i)
                if (h[i] < 1) h[i] = 1;
            break;
        }
        case 6: {
            // Many equal / plateau segments
            N = rnd.next(5, 25);
            vector<int> vals = {3, 5, 7};
            while ((int)h.size() < N) {
                int val = rnd.any(vals);
                int maxlen = min(5, N - (int)h.size());
                int len = rnd.next(1, maxlen);
                for (int j = 0; j < len; ++j)
                    h.push_back(val);
            }
            break;
        }
        case 7: {
            // Zig-zag high/low pattern
            N = rnd.next(6, 20);
            h.resize(N);
            int low = rnd.next(1, 5);
            int high = low + rnd.next(2, 7);
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) h[i] = high;
                else h[i] = low;
            }
            break;
        }
        case 8: {
            // Fixed sample from statement
            N = 8;
            h = {3, 7, 1, 6, 3, 5, 1, 7};
            break;
        }
        case 9: {
            // Custom symmetric tricky pattern
            // Designed to have multiple nearest candidates and equal heights
            N = 9;
            h = {5, 1, 4, 2, 3, 2, 4, 1, 5};
            break;
        }
    }

    // Output
    println(N);
    println(h);

    return 0;
}
