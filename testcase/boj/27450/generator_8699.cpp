#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with some variability but keep it small enough to read
    int N;
    int diceN = rnd.next(0, 9);
    if (diceN < 3)      N = rnd.next(1, 5);    // small
    else if (diceN < 8) N = rnd.next(6, 20);   // medium
    else                N = rnd.next(21, 40);  // larger but still readable

    // Choose K type
    int KType = rnd.next(0, 3);
    int K;
    if (KType == 0) {
        K = 1;
    } else if (KType == 1) {
        K = N;
    } else if (KType == 2) {
        // K > N, but not huge
        int maxK = min(500000, N + 20);
        if (N == maxK) {
            K = N;
        } else {
            K = rnd.next(N + 1, maxK);
        }
    } else {
        // Random K inside [1..max]
        if (N == 1) {
            K = 1;
        } else {
            int lo = 2;
            int hi = max(2, N - 1);
            K = rnd.next(lo, hi);
        }
    }

    vector<long long> p(N), t(N);

    // Choose pattern for p and t
    int pattern = rnd.next(0, 6);

    if (pattern == 0) {
        // All already strong: t_i <= p_i
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 30);
            int decMax = (int)p[i];
            int dec = (decMax > 0 ? rnd.next(0, decMax) : 0);
            t[i] = p[i] - dec;
        }
    } else if (pattern == 1) {
        // Prefix needs power, suffix already strong
        int pivot = rnd.next(1, N); // first 'pivot' positions need
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 20);
            if (i + 1 <= pivot) {
                long long add = rnd.next(1, 30);
                t[i] = p[i] + add;
            } else {
                int decMax = (int)p[i];
                int dec = (decMax > 0 ? rnd.next(0, decMax) : 0);
                t[i] = p[i] - dec;
            }
        }
    } else if (pattern == 2) {
        // Suffix needs power, prefix already strong
        int pivot = rnd.next(0, N - 1); // positions > pivot need
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 20);
            if (i <= pivot) {
                int decMax = (int)p[i];
                int dec = (decMax > 0 ? rnd.next(0, decMax) : 0);
                t[i] = p[i] - dec;
            } else {
                long long add = rnd.next(1, 30);
                t[i] = p[i] + add;
            }
        }
    } else if (pattern == 3) {
        // Alternating need / no-need by position
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 15);
            if (i % 2 == 0) { // 1-based odd positions: usually need
                long long add = rnd.next(0, 25);
                t[i] = p[i] + add;
            } else {
                int decMax = (int)p[i];
                int dec = (decMax > 0 ? rnd.next(0, decMax) : 0);
                t[i] = p[i] - dec;
            }
        }
    } else if (pattern == 4) {
        // Non-decreasing deficits across the line
        long long needPrev = rnd.next(0, 5);
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 5);
            long long inc = rnd.next(0, 5);
            needPrev = min(needPrev + inc, 50LL);
            t[i] = p[i] + needPrev;
        }
    } else if (pattern == 5) {
        // Random small values (including both p_i >= t_i and p_i < t_i)
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, 50);
            t[i] = rnd.next(0, 50);
        }
    } else if (pattern == 6) {
        // Random large values up to 1e9
        for (int i = 0; i < N; ++i) {
            p[i] = rnd.next(0, (int)1e9);
            t[i] = rnd.next(0, (int)1e9);
        }
    }

    println(N, K);
    println(p);
    println(t);

    return 0;
}
