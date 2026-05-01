#include "testlib.h"
using namespace std;

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXV = 1000000000000000000LL;

    // Precompute powers of two up to MAXV
    vector<long long> pow2;
    long long val = 1;
    while (val <= MAXV) {
        pow2.push_back(val);
        if (val > MAXV / 2) break;
        val *= 2;
    }

    int scenario = rnd.next(1, 10);
    long long A = 1, B = 1;

    switch (scenario) {
        case 1: { // Equal numbers, small or large
            long long equalVal;
            if (rnd.next(0, 1) == 0)
                equalVal = rnd.next(1LL, 50LL);
            else
                equalVal = rnd.next(100000000000000000LL, MAXV);
            A = B = equalVal;
            break;
        }
        case 2: { // Small coprime distinct numbers
            while (true) {
                A = rnd.next(1LL, 50LL);
                B = rnd.next(1LL, 50LL);
                if (A != B && gcdll(A, B) == 1) break;
            }
            break;
        }
        case 3: { // One is power of two, other is 1 or neighbor
            long long p = rnd.any(pow2); // p >= 1, <= MAXV
            int type = rnd.next(0, 2);
            if (type == 0) {
                A = 1;
                B = p;
            } else if (type == 1) {
                A = p;
                B = 1;
            } else {
                A = p;
                if (p + 1 <= MAXV) B = p + 1;
                else B = p - 1; // safety, though p+1 should fit with our pow2 list
            }
            break;
        }
        case 4: { // Very unbalanced: small vs huge
            long long small = rnd.next(1LL, 20LL);
            long long big = rnd.next(100000000000000000LL, MAXV);
            if (rnd.next(0, 1) == 0) {
                A = small;
                B = big;
            } else {
                A = big;
                B = small;
            }
            break;
        }
        case 5: { // Both random in full range
            A = rnd.next(1LL, MAXV);
            B = rnd.next(1LL, MAXV);
            break;
        }
        case 6: { // Consecutive large numbers
            long long x = rnd.next(100000000000000000LL, MAXV - 1);
            A = x;
            B = x + 1;
            if (rnd.next(0, 1) == 1) swap(A, B);
            break;
        }
        case 7: { // Multiples: B = k * A (or reversed)
            while (true) {
                long long base = rnd.next(1LL, 1000000000LL);
                long long maxK = MAXV / base;
                if (maxK >= 2) {
                    long long upperK = maxK;
                    if (upperK > 1000000000LL) upperK = 1000000000LL;
                    long long K = rnd.next(2LL, upperK);
                    if (rnd.next(0, 1) == 0) {
                        A = base;
                        B = base * K;
                    } else {
                        A = base * K;
                        B = base;
                    }
                    break;
                }
            }
            break;
        }
        case 8: { // Share a large power-of-two factor
            int maxIdx = (int)pow2.size() - 1;
            int idxLimit = min(maxIdx, 40); // up to 2^40
            int idx = rnd.next(1, idxLimit); // avoid 2^0 to emphasize factor
            long long factor = pow2[idx];
            long long limit = MAXV / factor;
            if (limit < 1) limit = 1;
            long long x = rnd.next(1LL, min(limit, 1000000LL));
            long long y = rnd.next(1LL, min(limit, 1000000LL));
            A = factor * x;
            B = factor * y;
            if (A < 1) A = 1;
            if (B < 1) B = 1;
            break;
        }
        case 9: { // Near powers of two
            int idx = rnd.next(1, (int)pow2.size() - 1); // p >= 2
            long long p = pow2[idx];
            int type = rnd.next(0, 2);
            if (type == 0) {
                A = p - 1;
                B = (p + 1 <= MAXV ? p + 1 : p);
            } else if (type == 1) {
                A = p - 1;
                B = p;
            } else {
                A = p;
                B = (p + 1 <= MAXV ? p + 1 : p - 1);
            }
            break;
        }
        case 10: { // Hard-coded extremes
            vector<pair<long long,long long>> cand;
            cand.push_back({1LL, 1LL});
            cand.push_back({1LL, MAXV});
            cand.push_back({MAXV, MAXV - 1});
            cand.push_back({MAXV, MAXV});
            cand.push_back({999999999999999937LL, 999999999999999929LL});
            pair<long long,long long> p = rnd.any(cand);
            A = p.first;
            B = p.second;
            break;
        }
        default: { // Fallback: random
            A = rnd.next(1LL, MAXV);
            B = rnd.next(1LL, MAXV);
            break;
        }
    }

    println(A, B);
    return 0;
}
