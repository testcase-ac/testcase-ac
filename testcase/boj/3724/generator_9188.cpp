#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = 1;
    println(T);

    int mode = rnd.next(0, 2); // 0: positive max, 1: negative max, 2: zero max

    int N = rnd.next(3, 7);
    int M = rnd.next(3, 8);

    vector<vector<int>> a(N, vector<int>(M));

    int best2 = M - 1;
    int best1 = rnd.next(0, M - 2); // another column < best2

    if (mode == 0) {
        // Positive maximum, two identical max-product columns (overflow-safe in 64-bit, not in 32-bit)
        int k = min(4, N);
        // Fill best1 and best2
        for (int i = 0; i < N; i++) {
            int val = (i < k ? 50000 : 1);
            a[i][best1] = val;
            a[i][best2] = val;
        }

        // Other columns: diverse patterns
        for (int j = 0; j < M; j++) {
            if (j == best1 || j == best2) continue;
            int pat = rnd.next(0, 4);
            if (pat == 0) {
                // All zeros
                for (int i = 0; i < N; i++) a[i][j] = 0;
            } else if (pat == 1) {
                // Checkerboard -2, 2
                for (int i = 0; i < N; i++) a[i][j] = (i % 2 == 0 ? -2 : 2);
            } else if (pat == 2) {
                // All -1
                for (int i = 0; i < N; i++) a[i][j] = -1;
            } else if (pat == 3) {
                // All small positives
                for (int i = 0; i < N; i++) a[i][j] = rnd.next(1, 3);
            } else {
                // Random small ints in [-3,3]
                for (int i = 0; i < N; i++) {
                    int x = rnd.next(-3, 3);
                    a[i][j] = x;
                }
            }
        }
    } else if (mode == 1) {
        // Negative maximum, all products negative, best = -1 (two columns tied)
        // Best columns: exactly one -1, others 1 -> product = -1
        int negPos = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++) {
            int val = (i == negPos ? -1 : 1);
            a[i][best1] = val;
            a[i][best2] = val;
        }

        for (int j = 0; j < M; j++) {
            if (j == best1 || j == best2) continue;
            int pat = rnd.next(0, 2);
            if (pat == 0) {
                // One -2, rest 1 -> product = -2
                int p = rnd.next(0, N - 1);
                for (int i = 0; i < N; i++) a[i][j] = (i == p ? -2 : 1);
            } else if (pat == 1) {
                // One -3, rest 1 -> product = -3
                int p = rnd.next(0, N - 1);
                for (int i = 0; i < N; i++) a[i][j] = (i == p ? -3 : 1);
            } else {
                // Three negatives: -1, -1, -2, rest 1 -> product negative (<= -2)
                int p1 = rnd.next(0, N - 1);
                int p2;
                do { p2 = rnd.next(0, N - 1); } while (p2 == p1);
                int p3;
                do { p3 = rnd.next(0, N - 1); } while (p3 == p1 || p3 == p2);
                for (int i = 0; i < N; i++) a[i][j] = 1;
                a[p1][j] = -1;
                a[p2][j] = -1;
                a[p3][j] = -2;
            }
        }
    } else {
        // mode == 2: Zero maximum, two columns with product 0, others strictly negative
        // Best columns: one zero, rest 1 -> product = 0
        int zeroPos = rnd.next(0, N - 1);
        for (int i = 0; i < N; i++) {
            int val = (i == zeroPos ? 0 : 1);
            a[i][best1] = val;
            a[i][best2] = val;
        }

        for (int j = 0; j < M; j++) {
            if (j == best1 || j == best2) continue;
            int pat = rnd.next(0, 2);
            if (pat == 0) {
                // One -1, rest 1 -> product = -1
                int p = rnd.next(0, N - 1);
                for (int i = 0; i < N; i++) a[i][j] = (i == p ? -1 : 1);
            } else if (pat == 1) {
                // One -2, rest 1 -> product = -2
                int p = rnd.next(0, N - 1);
                for (int i = 0; i < N; i++) a[i][j] = (i == p ? -2 : 1);
            } else {
                // Three -1, rest 1 -> product = -1
                int p1 = rnd.next(0, N - 1);
                int p2;
                do { p2 = rnd.next(0, N - 1); } while (p2 == p1);
                int p3;
                do { p3 = rnd.next(0, N - 1); } while (p3 == p1 || p3 == p2);
                for (int i = 0; i < N; i++) a[i][j] = 1;
                a[p1][j] = -1;
                a[p2][j] = -1;
                a[p3][j] = -1;
            }
        }
    }

    // Output single test case
    println(M, N);
    for (int i = 0; i < N; i++) {
        println(a[i]);
    }

    return 0;
}
