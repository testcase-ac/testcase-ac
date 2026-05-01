#include "testlib.h"
using namespace std;

int randomEven() {
    return 2 * rnd.next(1, 500000);
}

int randomOdd() {
    return 2 * rnd.next(1, 500000) - 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 0, K = 1;
    vector<int> S;

    int scenario = rnd.next(0, 8);

    switch (scenario) {
        // 0: All even numbers, various K
        case 0: {
            N = rnd.next(1, 25);
            S.resize(N);
            for (int i = 0; i < N; ++i) S[i] = randomEven();
            if (rnd.next(0, 1) == 0) {
                K = rnd.next(1, max(1, min(N, 5)));
            } else {
                K = rnd.next(max(1, N), N + 5);
            }
            break;
        }
        // 1: All odd numbers, answer always 0
        case 1: {
            N = rnd.next(1, 25);
            S.resize(N);
            for (int i = 0; i < N; ++i) S[i] = randomOdd();
            if (rnd.next(0, 2) == 0) {
                K = rnd.next(1, max(1, min(N, 5)));
            } else {
                int hi = min(100000, N + 50);
                K = rnd.next(1, hi);
            }
            break;
        }
        // 2: Alternating even/odd starting with even
        case 2: {
            N = rnd.next(2, 30);
            S.resize(N);
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) S[i] = randomEven();
                else S[i] = randomOdd();
            }
            K = rnd.next(1, N);
            break;
        }
        // 3: Alternating starting with odd
        case 3: {
            N = rnd.next(2, 30);
            S.resize(N);
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0) S[i] = randomOdd();
                else S[i] = randomEven();
            }
            K = rnd.next(1, N);
            break;
        }
        // 4: One large even block, odds elsewhere (plus a bit of noise)
        case 4: {
            N = rnd.next(10, 30);
            S.assign(N, 0);
            int L = rnd.next(3, max(3, N - 3));
            int st = rnd.next(0, N - L);
            for (int i = 0; i < N; ++i) {
                if (i >= st && i < st + L) {
                    S[i] = randomEven();
                } else {
                    S[i] = randomOdd();
                }
            }
            // Add some noise: flip a few odds outside the block to even
            for (int i = 0; i < N; ++i) {
                if (i < st || i >= st + L) {
                    if (rnd.next(0, 9) < 3) { // 30% chance
                        S[i] = randomEven();
                    }
                }
            }
            int cntOdd = 0;
            for (int x : S) if (x % 2 != 0) ++cntOdd;
            if (cntOdd == 0) cntOdd = 1; // avoid K only being 0
            int type = rnd.next(0, 3);
            if (type == 0) K = rnd.next(1, cntOdd);
            else if (type == 1) K = cntOdd;
            else K = min(100000, cntOdd + rnd.next(1, 5));
            break;
        }
        // 5: Fully random parity with different even density
        case 5: {
            N = rnd.next(1, 30);
            S.resize(N);
            double pEven;
            int pick = rnd.next(0, 2);
            if (pick == 0) pEven = 0.2;
            else if (pick == 1) pEven = 0.5;
            else pEven = 0.8;
            for (int i = 0; i < N; ++i) {
                if (rnd.next() < pEven) S[i] = randomEven();
                else S[i] = randomOdd();
            }
            int hiK = min(100000, N + 5);
            K = rnd.next(1, hiK);
            break;
        }
        // 6: Odds at both ends, mixed middle
        case 6: {
            N = rnd.next(5, 30);
            S.resize(N);
            S[0] = randomOdd();
            S[N - 1] = randomOdd();
            for (int i = 1; i < N - 1; ++i) {
                if (rnd.next(0, 9) < 7) S[i] = randomEven();
                else S[i] = randomOdd();
            }
            K = rnd.next(1, max(3, min(10, N + 3)));
            break;
        }
        // 7: K is very large compared to N
        case 7: {
            N = rnd.next(5, 20);
            S.resize(N);
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1) == 0) S[i] = randomEven();
                else S[i] = randomOdd();
            }
            K = 100000;
            break;
        }
        // 8: N = 1 boundary case
        case 8: {
            N = 1;
            S.resize(N);
            if (rnd.next(0, 1) == 0) S[0] = randomEven();
            else S[0] = randomOdd();
            K = rnd.next(1, 100000);
            break;
        }
    }

    println(N, K);
    println(S);

    return 0;
}
