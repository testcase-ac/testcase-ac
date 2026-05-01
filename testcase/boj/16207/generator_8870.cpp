#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> A;
    int type = rnd.next(0, 9);

    if (type == 0) {
        // Very small N, often no rectangle possible
        int N = rnd.next(1, 3);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(2, 10);
        }
    } else if (type == 1) {
        // All equal lengths
        int N = rnd.next(4, 20);
        int x;
        if (rnd.next(0, 2) < 2) {
            x = rnd.next(2, 30);
        } else {
            x = rnd.next(90000, 100000);
        }
        A.assign(N, x);
    } else if (type == 2) {
        // Two values differing by exactly 1
        int N = rnd.next(4, 30);
        int base = rnd.next(2, 99999);
        int high = base + 1;
        int c1 = rnd.next(1, N - 1);
        int c2 = N - c1;
        for (int i = 0; i < c1; i++) A.push_back(base);
        for (int i = 0; i < c2; i++) A.push_back(high);
    } else if (type == 3) {
        // Random small values
        int N = rnd.next(10, 40);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(2, 30);
        }
    } else if (type == 4) {
        // Ascending arithmetic progression
        int N = rnd.next(4, 20);
        int start = rnd.next(2, 10);
        int step = rnd.next(1, 3);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i] = start + i * step;
        }
    } else if (type == 5) {
        // Values drawn from a small pool (with duplicates)
        int N = rnd.next(5, 30);
        int K = rnd.next(2, 7);
        vector<int> pool;
        for (int i = 0; i < K; i++) {
            pool.push_back(rnd.next(2, 25));
        }
        for (int i = 0; i < N; i++) {
            A.push_back(rnd.any(pool));
        }
    } else if (type == 6) {
        // Mixed extremes: very small and very large values
        int N = rnd.next(10, 25);
        vector<int> pool = {
            2, 3, 4, 5, 6, 7, 8, 9, 10,
            50, 99, 100, 999, 1000, 9999,
            10000, 50000, 99999, 100000
        };
        for (int i = 0; i < N; i++) {
            // Slight bias towards larger numbers
            if (rnd.next(0, 3) == 0) {
                A.push_back(pool[rnd.next(9, (int)pool.size() - 1)]);
            } else {
                A.push_back(rnd.any(pool));
            }
        }
    } else if (type == 7) {
        // Designed to have (at least) one clear rectangle plus noise
        int base1 = rnd.next(2, 30);
        int base2 = rnd.next(2, 30);
        if (base1 == base2) base2 = min(30, base2 + 1);
        A.push_back(base1);
        A.push_back(base1);
        A.push_back(base2);
        A.push_back(base2);
        int N = rnd.next(4, 8);
        while ((int)A.size() < N) {
            // Add some noise lengths which rarely pair nicely
            int v = rnd.next(2, 35);
            if (abs(v - base1) > 1 && abs(v - base2) > 1) {
                A.push_back(v);
            }
        }
    } else if (type == 8) {
        // Triples of [x, x, x+1] – tricky cut decisions
        int groups = rnd.next(1, 5);
        for (int g = 0; g < groups; g++) {
            int base;
            if (rnd.next(0, 1) == 0)
                base = rnd.next(2, 25);
            else
                base = rnd.next(90000, 99999);
            A.push_back(base);
            A.push_back(base);
            A.push_back(base + 1);
        }
    } else if (type == 9) {
        // Many potential rectangles: values around a base
        int N = rnd.next(25, 40);
        int base = rnd.next(2, 99998); // so base+2 <= 100000
        for (int i = 0; i < N; i++) {
            int r = rnd.next(0, 99);
            if (r < 60) {
                A.push_back(base);
            } else if (r < 95) {
                A.push_back(base + 1);
            } else {
                A.push_back(base + 2);
            }
        }
    }

    shuffle(A.begin(), A.end());
    int N = (int)A.size();
    println(N);
    println(A);

    return 0;
}
