#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXA = 1000000000000000000LL;

    int Q = rnd.next(6, 11);
    vector<pair<long long, long long>> qs;
    qs.reserve(Q);

    // Fixed diverse edge / sample cases
    qs.push_back({1LL, 2LL});                 // smallest valid
    qs.push_back({1LL, 1LL});                 // smallest invalid (b = a)
    qs.push_back({2LL, 3LL});                 // sample invalid (not divisible)
    qs.push_back({2LL, 4LL});                 // small valid (b = 2a)
    qs.push_back({MAXA, MAXA});               // large invalid (b = a)
    qs.push_back({MAXA / 2, MAXA});           // large valid (b = 2a)

    while ((int)qs.size() < Q) {
        int mode = rnd.next(0, 3);
        long long a, b;

        if (mode == 0) {
            // Random valid: b divisible by a and b >= 2a
            while (true) {
                a = rnd.next(1LL, MAXA);
                long long maxK = MAXA / a;
                if (maxK < 2) continue;

                long long k;
                if (maxK <= 5) {
                    k = rnd.next(2LL, maxK);
                } else {
                    int style = rnd.next(0, 2);
                    if (style == 0) k = 2;
                    else if (style == 1) k = 3;
                    else {
                        long long upper = min(maxK, 100LL);
                        k = rnd.next(2LL, upper);
                    }
                }

                b = (long long)((__int128)a * k);
                if (b >= 1 && b <= MAXA) break;
            }
        } else if (mode == 1) {
            // Mostly invalid: random, tweak if it accidentally becomes valid
            while (true) {
                a = rnd.next(1LL, MAXA);
                b = rnd.next(1LL, MAXA);

                if (b % a == 0 && b / a >= 2) {
                    if (b + 1 <= MAXA) b++;
                    else if (b - 1 >= 1) b--;
                    else continue;
                }
                break;
            }
        } else if (mode == 2) {
            // Boundary near 2a: b = 2a ± 1
            while (true) {
                a = rnd.next(1LL, MAXA);
                bool plus = rnd.next(0, 1);
                __int128 tmp = (__int128)2 * a + (plus ? 1 : -1);
                if (tmp < 1 || tmp > MAXA) continue;
                b = (long long)tmp;
                break;
            }
        } else {
            // Small random, easy to verify by hand
            a = rnd.next(1LL, 30LL);
            b = rnd.next(1LL, 60LL);
        }

        qs.push_back({a, b});
    }

    println(Q);
    for (auto &p : qs) {
        println(p.first, p.second);
    }

    return 0;
}
