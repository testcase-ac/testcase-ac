#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int AMIN = 2;
    const int AMAX = 100000000;

    int variant = rnd.next(0, 6);
    int N;
    vector<int> a;

    switch (variant) {
        case 0: {
            // Very small N, small a_i
            N = rnd.next(1, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(2, 10);
            break;
        }
        case 1: {
            // Medium N, moderate a_i
            N = rnd.next(5, 20);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(2, 100);
            break;
        }
        case 2: {
            // Mix of very small and very large a_i
            N = rnd.next(5, 25);
            a.resize(N);
            vector<int> smallVals = {2, 3, 4, 5, 6, 7, 8, 9, 10};
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0)
                    a[i] = rnd.any(smallVals);
                else
                    a[i] = rnd.next(1000, AMAX);
            }
            break;
        }
        case 3: {
            // Roughly monotone sequence, with some clamping to edges
            N = rnd.next(5, 30);
            a.resize(N);
            long long cur = rnd.next(2, AMAX);
            int stepAmp = rnd.next(0, 1000000);
            bool inc = rnd.next(0, 1);
            for (int i = 0; i < N; ++i) {
                if (cur < AMIN) cur = AMIN;
                if (cur > AMAX) cur = AMAX;
                a[i] = (int)cur;
                long long delta = stepAmp == 0 ? 0 : rnd.next(0, stepAmp);
                if (inc) cur += delta;
                else cur -= delta;
            }
            break;
        }
        case 4: {
            // Many repeats from a few distinct values
            N = rnd.next(10, 35);
            int k = rnd.next(1, 4);
            vector<int> vals;
            for (int i = 0; i < k; ++i) {
                int v = rnd.next(AMIN, AMAX);
                vals.push_back(v);
            }
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.any(vals);
            // Occasionally sort, sometimes not
            if (rnd.next(0, 1)) {
                sort(a.begin(), a.end());
                if (rnd.next(0, 1))
                    reverse(a.begin(), a.end());
            }
            break;
        }
        case 5: {
            // All values very large, near AMAX
            N = rnd.next(20, 40);
            a.resize(N);
            int base = rnd.next(max(AMIN, AMAX - 1000), AMAX);
            for (int i = 0; i < N; ++i) {
                int off = rnd.next(0, 1000);
                long long v = (long long)base - off;
                if (v < AMIN) v = AMIN;
                a[i] = (int)v;
            }
            break;
        }
        case 6: {
            // Tiny N (1 or 2), edge values
            int pattern = rnd.next(0, 4);
            if (pattern == 0) {
                N = 1;
                a = {2};
            } else if (pattern == 1) {
                N = 1;
                a = {AMAX};
            } else if (pattern == 2) {
                N = 2;
                a = {2, 2};
            } else if (pattern == 3) {
                N = 2;
                a = {2, AMAX};
            } else {
                N = 2;
                a = {AMAX, AMAX};
            }
            break;
        }
    }

    println(N);
    println(a);

    return 0;
}
