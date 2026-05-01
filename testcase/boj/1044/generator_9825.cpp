#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto randomEven = [&](int lo, int hi) -> int {
        int x;
        do {
            x = rnd.next(lo, hi);
        } while (x % 2 != 0);
        return x;
    };

    int type = rnd.next(0, 7);
    int N;
    vector<long long> a, b;

    switch (type) {
        case 0: {
            // Minimal case N = 2, small values
            N = 2;
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1, 20);
                b[i] = rnd.next(1, 20);
            }
            break;
        }
        case 1: {
            // Small even N in {2,4,6,8,10}, moderate values
            N = 2 * rnd.next(1, 5); // 2..10
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1, 1000);
                b[i] = rnd.next(1, 1000);
            }
            break;
        }
        case 2: {
            // Medium N in [10,20] even, larger values (to stress sums / overflow)
            N = randomEven(10, 20);
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1LL, 1000000000LL);
                b[i] = rnd.next(1LL, 1000000000LL);
            }
            break;
        }
        case 3: {
            // Every player has a_i + b_i = constant C -> all partitions give same score diff
            N = randomEven(4, 20);
            a.resize(N);
            b.resize(N);
            long long C = rnd.next(20LL, 1000LL);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1LL, C - 1);  // ensure b[i] >= 1
                b[i] = C - a[i];
            }
            break;
        }
        case 4: {
            // a[i] == b[i] for all i, many close partitions, strong tie behavior
            N = randomEven(4, 20);
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1LL, 1000LL);
                b[i] = a[i];
            }
            break;
        }
        case 5: {
            // All a[i] = A, all b[i] = B -> diff independent of partition
            N = randomEven(4, 20);
            a.resize(N);
            b.resize(N);
            long long A = rnd.next(1LL, 1000LL);
            long long B = rnd.next(1LL, 1000LL);
            for (int i = 0; i < N; ++i) {
                a[i] = A;
                b[i] = B;
            }
            break;
        }
        case 6: {
            // Small N, very large values up to 1e15 (check 64-bit usage)
            int options[4] = {2, 4, 6, 8};
            N = options[rnd.next(0, 3)];
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1000000000LL, 1000000000000000LL);
                b[i] = rnd.next(1000000000LL, 1000000000000000LL);
            }
            break;
        }
        case 7: {
            // One "star" player with much larger scores than others
            N = randomEven(4, 20);
            a.resize(N);
            b.resize(N);
            for (int i = 0; i < N; ++i) {
                a[i] = rnd.next(1LL, 1000LL);
                b[i] = rnd.next(1LL, 1000LL);
            }
            int p;
            int choice = rnd.next(0, 2);
            if (choice == 0)
                p = 0;
            else if (choice == 1)
                p = N - 1;
            else
                p = rnd.next(0, N - 1);
            a[p] = rnd.next(100000000LL, 1000000000LL);
            b[p] = rnd.next(100000000LL, 1000000000LL);
            break;
        }
    }

    println(N);
    println(a);
    println(b);

    return 0;
}
