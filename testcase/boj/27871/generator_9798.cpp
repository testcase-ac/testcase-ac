#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long BIG = 1000000000000000000LL;

    int T = rnd.next(1, 7);
    int totalNLimit = rnd.next(T, 3 * T + 2);

    println(T);

    int remain = totalNLimit;

    for (int tc = 0; tc < T; ++tc) {
        int testsLeft = T - tc;
        int maxNByRemain = remain - (testsLeft - 1);
        if (maxNByRemain < 1) maxNByRemain = 1;

        int scen = rnd.next(0, 6);
        int desiredMaxN = (scen == 4 ? 3 : 8); // big-number scenario uses smaller N
        int maxN = min(desiredMaxN, maxNByRemain);
        if (maxN < 1) maxN = 1;

        int N = rnd.next(1, maxN);
        remain -= N;

        long long P;
        vector<long long> C(N, 0);

        switch (scen) {
            case 0: {
                // Small P, small coins
                P = rnd.next(1LL, 5LL);
                for (int i = 0; i < N; ++i) {
                    C[i] = rnd.next(0LL, 7LL);
                }
                break;
            }
            case 1: {
                // Coins around multiples of (P+1)
                P = rnd.next(2LL, 10LL);
                for (int i = 0; i < N; ++i) {
                    long long k = rnd.next(0LL, 3LL);
                    long long r = rnd.next(0LL, P);
                    C[i] = k * (P + 1) + r;
                }
                break;
            }
            case 2: {
                // P = 1
                P = 1;
                for (int i = 0; i < N; ++i) {
                    C[i] = rnd.next(0LL, 10LL);
                }
                break;
            }
            case 3: {
                // P = 2 or 3, many zeros
                P = (rnd.next(0, 1) ? 2LL : 3LL);
                for (int i = 0; i < N; ++i) {
                    if (rnd.next(0, 2) == 0)
                        C[i] = 0;
                    else
                        C[i] = rnd.next(1LL, 5LL);
                }
                break;
            }
            case 4: {
                // Big P and potentially big coins
                if (rnd.next(0, 2) == 0) P = BIG;
                else P = rnd.next(50LL, 1000000000000LL);
                for (int i = 0; i < N; ++i) {
                    int r = rnd.next(0, 2);
                    if (r == 0)
                        C[i] = rnd.next(0LL, 1000000LL);
                    else if (r == 1)
                        C[i] = rnd.next(1000000000LL, 1000000000000LL);
                    else
                        C[i] = rnd.next(1000000000000LL, BIG);
                }
                break;
            }
            case 5: {
                // Many zeros, some random nonzero positions
                P = rnd.next(1LL, 10LL);
                vector<int> idx(N);
                for (int i = 0; i < N; ++i) idx[i] = i;
                shuffle(idx.begin(), idx.end());
                int nonZeroCount = rnd.next(1, N);
                for (int k = 0; k < nonZeroCount; ++k) {
                    int pos = idx[k];
                    C[pos] = rnd.next(1LL, 10LL);
                }
                break;
            }
            case 6: {
                // Monotone patterns
                P = rnd.next(1LL, 12LL);
                bool increasing = rnd.next(0, 1);
                if (increasing) {
                    long long start = rnd.next(0LL, 3LL);
                    long long step = rnd.next(0LL, 3LL);
                    for (int i = 0; i < N; ++i) {
                        C[i] = start + step * i;
                    }
                } else {
                    long long start = rnd.next(0LL, 6LL);
                    long long step = rnd.next(0LL, 3LL);
                    for (int i = 0; i < N; ++i) {
                        long long val = start - step * i;
                        if (val < 0) val = 0;
                        C[i] = val;
                    }
                }
                break;
            }
        }

        // Ensure top-most stair has at least one coin: C_N != 0
        if (C[N - 1] == 0) {
            if (scen == 4)
                C[N - 1] = rnd.next(1LL, 1000000000000LL);
            else
                C[N - 1] = rnd.next(1LL, 10LL);
        }

        println(N, P);
        println(C);
    }

    return 0;
}
