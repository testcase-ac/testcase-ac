#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide size range type
    int sizeType = rnd.next(1, 4);
    int N;
    if (sizeType == 1) N = rnd.next(1, 5);       // very small
    else if (sizeType == 2) N = rnd.next(5, 10); // small
    else if (sizeType == 3) N = rnd.next(10, 20);// medium
    else N = rnd.next(20, 40);                   // upper bound (still hand-checkable)

    vector<int> a;
    a.reserve(N);

    if (N == 1) {
        a.push_back(rnd.next(1, 1000000));
    } else {
        int pattern = rnd.next(0, 6); // choose among 7 different patterns

        switch (pattern) {
            case 0: {
                // Strictly increasing sequence
                int start = rnd.next(1, 10);
                int step = rnd.next(1, 5);
                for (int i = 0; i < N; ++i)
                    a.push_back(start + i * step);
                break;
            }
            case 1: {
                // Strictly decreasing sequence
                int start = rnd.next(N + 1, N + 10);
                for (int i = 0; i < N; ++i)
                    a.push_back(start - i);
                break;
            }
            case 2: {
                // All equal values (tests strict vs non-strict LIS handling)
                int v = rnd.next(1, 1000000);
                for (int i = 0; i < N; ++i)
                    a.push_back(v);
                break;
            }
            case 3: {
                // Random values with varying value range
                vector<int> Ks = {5, 10, 100, 1000000};
                int K = rnd.any(Ks);
                for (int i = 0; i < N; ++i)
                    a.push_back(rnd.next(1, K));
                break;
            }
            case 4: {
                // Wave pattern: small, big, small, big, ...
                int small = rnd.next(1, 10);
                int big = small + rnd.next(1, 10);
                for (int i = 0; i < N; ++i)
                    a.push_back((i % 2 == 0) ? small : big);
                break;
            }
            case 5: {
                // Mostly increasing with occasional drops
                int cur = rnd.next(10, 20);
                for (int i = 0; i < N; ++i) {
                    if (i > 0 && rnd.next(0, 4) == 0) { // 20% chance to drop
                        cur -= rnd.next(1, 5);
                        if (cur < 1) cur = 1;
                    } else {
                        cur += rnd.next(0, 5);
                        if (cur > 1000000) cur = 1000000;
                    }
                    a.push_back(cur);
                }
                break;
            }
            case 6: {
                // Non-decreasing blocks with duplicates
                int val = rnd.next(1, 10);
                while ((int)a.size() < N) {
                    int rem = N - (int)a.size();
                    int reps = rnd.next(1, min(3, rem));
                    for (int k = 0; k < reps; ++k)
                        a.push_back(val);
                    val += rnd.next(1, 5);
                    if (val > 1000000) val = 1000000;
                }
                break;
            }
        }
    }

    println(N);
    println(a);

    return 0;
}
