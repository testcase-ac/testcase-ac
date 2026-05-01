#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose pattern type
    int pattern = rnd.next(0, 7);
    int N;
    vector<int> a;

    switch (pattern) {
        case 0: { // already sorted ascending, arithmetic-like
            N = rnd.next(1, 50);
            int base = rnd.next(-10, 10);
            int step = rnd.next(1, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = base + step * i;
            }
            break;
        }
        case 1: { // strictly decreasing
            N = rnd.next(1, 50);
            int base = rnd.next(-10, 10);
            int step = rnd.next(1, 5);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = base + step * i;
            }
            // make it decreasing
            reverse(a.begin(), a.end());
            break;
        }
        case 2: { // all equal (including boundaries)
            N = rnd.next(1, 50);
            vector<int> cand = {-2000000, -100, -1, 0, 1, 100, 2000000};
            int val = rnd.any(cand);
            a.assign(N, val);
            break;
        }
        case 3: { // many duplicates from small range
            N = rnd.next(5, 50);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(-5, 5);
            }
            break;
        }
        case 4: { // random distinct values in small range
            N = rnd.next(1, 40);
            vector<int> pool;
            for (int v = -20; v <= 20; ++v)
                pool.push_back(v);
            shuffle(pool.begin(), pool.end());
            a.assign(pool.begin(), pool.begin() + N);
            break;
        }
        case 5: { // fully random within full constraints
            N = rnd.next(1, 50);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(-2000000, 2000000);
            }
            break;
        }
        case 6: { // nearly sorted: sorted then a few random swaps
            N = rnd.next(5, 50);
            a.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(-1000, 1000);
            }
            sort(a.begin(), a.end());
            int k = rnd.next(1, max(1, N / 5));
            for (int i = 0; i < k; ++i) {
                int x = rnd.next(0, N - 1);
                int y = rnd.next(0, N - 1);
                swap(a[x], a[y]);
            }
            break;
        }
        case 7: { // zigzag pattern: alternating low/high values
            N = rnd.next(3, 50);
            a.resize(N);
            int lowStart = rnd.next(-100, -1);
            int highStart = rnd.next(1, 100);
            int lowStep = rnd.next(0, 3);   // allow repeats
            int highStep = rnd.next(0, 3);  // allow repeats
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) {
                    a[i] = highStart + highStep * (i / 2);
                } else {
                    a[i] = lowStart + lowStep * (i / 2);
                }
            }
            break;
        }
    }

    println(N);
    println(a);

    return 0;
}
