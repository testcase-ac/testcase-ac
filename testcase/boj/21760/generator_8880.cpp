#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long calcS(int N, int M, int k) {
    long long intra = 1LL * N * M * (M - 1) / 2;
    long long inter = 1LL * N * (N - 1) / 2 * 1LL * M * M;
    return intra * k + inter;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    struct Test {
        int N, M, k;
        long long D;
    };

    int tMode = rnd.next(0, 2);
    int T;
    if (tMode == 0) T = rnd.next(1, 3);
    else if (tMode == 1) T = rnd.next(4, 7);
    else T = rnd.next(8, 10);

    vector<Test> tests;
    tests.reserve(T);

    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 5);
        int N, M, k;
        long long D;

        switch (type) {
            // Small N,M, exact multiple (answer = D)
            case 0: {
                N = rnd.next(2, 5);
                M = rnd.next(2, 5);
                k = rnd.next(1, 5);
                long long S = calcS(N, M, k);
                long long Bmax = 1000000000LL / S;
                int Bhi = (int)min(5LL, Bmax);
                if (Bhi < 1) Bhi = 1;
                int B = rnd.next(1, Bhi);
                D = S * B;
                break;
            }
            // Small N,M, impossible (S > D, answer = -1)
            case 1: {
                N = rnd.next(2, 5);
                M = rnd.next(2, 5);
                k = rnd.next(1, 5);
                long long S = calcS(N, M, k);
                int hi = (int)min(S - 1, 1000000000LL);
                if (hi < 1) hi = 1;
                D = rnd.next(1, hi);
                break;
            }
            // Small N,M, D not a multiple of S (remainder case)
            case 2: {
                N = rnd.next(2, 5);
                M = rnd.next(2, 5);
                k = rnd.next(1, 5);
                long long S = calcS(N, M, k);
                long long Bmax = 1000000000LL / S;
                int Bhi = (int)min(5LL, Bmax);
                if (Bhi < 1) Bhi = 1;
                int B = rnd.next(1, Bhi);
                long long base = S * B;
                long long rmax = min(S - 1, 1000000000LL - base);
                int r = 1;
                if (rmax >= 1) r = rnd.next(1, (int)rmax);
                D = base + r;
                break;
            }
            // Large N,M,k, various D (exact / remainder / very large D)
            case 3: {
                N = rnd.next(50, 100);
                M = rnd.next(50, 100);
                k = rnd.next(50, 100);
                long long S = calcS(N, M, k);
                long long Bmax = 1000000000LL / S;
                int cap = (int)min(Bmax, 200LL);
                if (cap < 1) cap = 1;
                int B = rnd.next(1, cap);
                int pattern = rnd.next(0, 2); // 0: exact, 1: remainder, 2: D=1e9

                if (pattern == 0) {
                    D = S * B;
                } else if (pattern == 1) {
                    long long base = S * B;
                    long long rmax = min(S - 1, 1000000000LL - base);
                    if (rmax >= 1) {
                        int r = rnd.next(1, (int)rmax);
                        D = base + r;
                    } else {
                        D = base;
                    }
                } else {
                    D = 1000000000LL;
                }
                break;
            }
            // N=2 or M=2 edge cases, mix of possible/impossible/remainder
            case 4: {
                if (rnd.next(0, 1) == 0) {
                    N = 2;
                    M = rnd.next(2, 30);
                } else {
                    M = 2;
                    N = rnd.next(2, 30);
                }
                k = rnd.next(1, 30);
                long long S = calcS(N, M, k);
                long long Bmax = 1000000000LL / S;
                int pattern = rnd.next(0, 2); // 0: impossible, 1: exact, 2: remainder

                if (pattern == 0) {
                    int hi = (int)min(S - 1, 1000000000LL);
                    if (hi < 1) hi = 1;
                    D = rnd.next(1, hi);
                } else if (pattern == 1) {
                    int cap = (int)min(Bmax, 100LL);
                    if (cap < 1) cap = 1;
                    int B = rnd.next(1, cap);
                    D = S * B;
                } else {
                    int cap = (int)min(Bmax, 100LL);
                    if (cap < 1) cap = 1;
                    int B = rnd.next(1, cap);
                    long long base = S * B;
                    long long rmax = min(S - 1, 1000000000LL - base);
                    if (rmax >= 1) {
                        int r = rnd.next(1, (int)rmax);
                        D = base + r;
                    } else {
                        D = base;
                    }
                }
                break;
            }
            // k=1 special, mix of possible/impossible/remainder
            case 5: {
                N = rnd.next(2, 30);
                M = rnd.next(2, 30);
                k = 1;
                long long S = calcS(N, M, k);
                long long Bmax = 1000000000LL / S;
                int pattern = rnd.next(0, 2); // 0: impossible, 1: exact, 2: remainder

                if (pattern == 0) {
                    int hi = (int)min(S - 1, 1000000000LL);
                    if (hi < 1) hi = 1;
                    D = rnd.next(1, hi);
                } else if (pattern == 1) {
                    int cap = (int)min(Bmax, 100LL);
                    if (cap < 1) cap = 1;
                    int B = rnd.next(1, cap);
                    D = S * B;
                } else {
                    int cap = (int)min(Bmax, 100LL);
                    if (cap < 1) cap = 1;
                    int B = rnd.next(1, cap);
                    long long base = S * B;
                    long long rmax = min(S - 1, 1000000000LL - base);
                    if (rmax >= 1) {
                        int r = rnd.next(1, (int)rmax);
                        D = base + r;
                    } else {
                        D = base;
                    }
                }
                break;
            }
        }

        tests.push_back({N, M, k, D});
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (const auto &tc : tests) {
        println(tc.N, tc.M, tc.k, tc.D);
    }

    return 0;
}
