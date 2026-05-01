#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N, K;
    vector<int> a;

    int mode = rnd.next(0, 7); // choose a generation mode

    switch (mode) {
        case 0: {
            // Very small random case, including N=1 possibility
            N = rnd.next(1, 7);
            K = rnd.next(1, N);
            a.resize(N);
            for (int i = 0; i < N; ++i) a[i] = rnd.next(0, 20);
            break;
        }
        case 1: {
            // Many zeros, some small positives
            N = rnd.next(5, 15);
            K = rnd.next(1, N);
            a.resize(N);
            bool hasPositive = false;
            for (int i = 0; i < N; ++i) {
                int type = rnd.next(0, 4); // skew towards zeros
                if (type == 0) {
                    a[i] = rnd.next(1, 3);
                    hasPositive = true;
                } else {
                    a[i] = 0;
                }
            }
            // Ensure at least one positive with 50% chance
            if (!hasPositive && rnd.next(0, 1) == 0) {
                int pos = rnd.next(0, N - 1);
                a[pos] = rnd.next(1, 3);
            }
            break;
        }
        case 2: {
            // Monotone increasing or decreasing sequence
            N = rnd.next(5, 15);
            K = rnd.next(1, N);
            a.resize(N);
            bool increasing = rnd.next(0, 1);
            int base = rnd.next(0, 5);
            int step = rnd.next(0, 3); // can be 0 for flat portions
            if (increasing) {
                for (int i = 0; i < N; ++i)
                    a[i] = min(20, base + i * step);
            } else {
                for (int i = 0; i < N; ++i)
                    a[i] = max(0, 20 - (base + i * step));
            }
            break;
        }
        case 3: {
            // Alternating big and small (including zeros)
            N = rnd.next(6, 16);
            K = rnd.next(1, N);
            a.resize(N);
            int startBig = rnd.next(0, 1); // whether index 0 is big or small
            for (int i = 0; i < N; ++i) {
                bool big = ((i + startBig) % 2 == 0);
                if (big) {
                    // big values near maximum
                    a[i] = rnd.next(15, 20);
                } else {
                    // small or zero
                    int type = rnd.next(0, 2);
                    if (type == 0) a[i] = 0;
                    else a[i] = rnd.next(1, 3);
                }
            }
            break;
        }
        case 4: {
            // K = 1, everything in one group
            N = rnd.next(10, 25);
            K = 1;
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                // mix zeros and highs
                int type = rnd.next(0, 3);
                if (type == 0) a[i] = 0;
                else if (type == 1) a[i] = rnd.next(1, 5);
                else a[i] = rnd.next(15, 20);
            }
            break;
        }
        case 5: {
            // K = N, each group must be exactly one test paper
            N = rnd.next(5, 20);
            K = N;
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                // small values to keep sums small
                a[i] = rnd.next(0, 10);
            }
            break;
        }
        case 6: {
            // Medium-sized random with extremes to stress partitioning
            N = rnd.next(20, 40);
            K = rnd.next(1, N);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                int type = rnd.next(0, 4);
                if (type <= 1) a[i] = 0;              // many zeros
                else if (type == 2) a[i] = rnd.next(1, 5);
                else a[i] = rnd.next(15, 20);       // some large
            }
            break;
        }
        case 7: {
            // Crafted pattern: clusters of high values separated by small ones
            // This can trick naive "even length" partitions.
            N = 11;
            // Choose K so that it's neither trivial nor extreme
            K = rnd.next(2, 10);
            a = {10, 1, 1, 10, 1, 1, 10, 1, 1, 10, 1};
            // Optionally perturb a little while staying in [0,20]
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 3) == 0) {
                    int delta = rnd.next(-1, 1);
                    int v = a[i] + delta;
                    if (v < 0) v = 0;
                    if (v > 20) v = 20;
                    a[i] = v;
                }
            }
            break;
        }
    }

    println(N, K);
    println(a);

    return 0;
}
