#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 7);
    int N;
    vector<long long> a;

    switch (type) {
        case 0: {
            // All ones (good for checking off-by-one and zero-answer handling)
            N = rnd.next(1, 8);
            a.assign(N, 1LL);
            break;
        }
        case 1: {
            // Hand-crafted small cases (include samples and edge-like)
            int id = rnd.next(0, 4);
            if (id == 0) {
                N = 1;
                a = {5};
            } else if (id == 1) {
                N = 3;
                a = {2, 3, 4}; // sample 1
            } else if (id == 2) {
                N = 4;
                a = {100, 97, 90, 12}; // sample 2
            } else if (id == 3) {
                N = 3;
                a = {1, 1, 1}; // correct answer 0
            } else {
                N = 5;
                a = {1, 2, 3, 4, 5};
            }
            break;
        }
        case 2: {
            // Random small N, small values
            N = rnd.next(2, 8);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, 20);
            break;
        }
        case 3: {
            // Random medium N, moderate values
            N = rnd.next(9, 15);
            a.resize(N);
            for (int i = 0; i < N; ++i)
                a[i] = rnd.next(1, 100);
            break;
        }
        case 4: {
            // Increasing-ish pattern
            N = rnd.next(5, 15);
            long long base = rnd.next(1, 5);
            long long step = rnd.next(0, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                long long delta = rnd.next(-2, 2);
                long long val = base + step * i + delta;
                if (val < 1) val = 1;
                if (val > 1000000000LL) val = 1000000000LL;
                a[i] = val;
            }
            break;
        }
        case 5: {
            // Decreasing-ish pattern
            N = rnd.next(5, 15);
            long long start = rnd.next(5, 30);
            long long step = rnd.next(0, 3);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                long long delta = rnd.next(-2, 2);
                long long val = start - step * i + delta;
                if (val < 1) val = 1;
                if (val > 1000000000LL) val = 1000000000LL;
                a[i] = val;
            }
            break;
        }
        case 6: {
            // Values around the "distance" threshold: a_i ≈ N+1-i
            N = rnd.next(3, 10);
            a.resize(N);
            int k = rnd.next(1, N); // index where a_k == distance
            for (int i = 1; i <= N; ++i) {
                long long dist = N + 1 - i;
                long long val;
                if (i == k) {
                    val = dist; // exact threshold => final 0 if chosen
                } else {
                    int delta = rnd.next(-2, 2);
                    val = dist + delta;
                }
                if (val < 1) val = 1;
                if (val > 1000000000LL) val = 1000000000LL;
                a[i - 1] = val;
            }
            break;
        }
        case 7: {
            // Mix of small and very large values
            N = rnd.next(1, 25);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0) {
                    a[i] = rnd.next(1, 100);
                } else {
                    long long bigBase = 1000000000LL - rnd.next(0, 1000);
                    if (bigBase < 1) bigBase = 1;
                    a[i] = bigBase;
                }
            }
            break;
        }
    }

    println(N);
    println(a);

    return 0;
}
