#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 1, b = 2; // default, will be overwritten

    auto isPowerOfTwo = [&](int x) -> bool {
        return x > 0 && (x & (x - 1)) == 0;
    };

    int scenario = rnd.next(1, 6);

    if (scenario == 1) {
        // Small representable: small power-of-two denominator
        int q = rnd.next(1, 5);  // b = 2..32
        b = 1 << q;
        int maxK = (b / 2) - 1;  // number of possible odd values
        int k = rnd.next(0, maxK);
        a = 2 * k + 1;           // odd, 1 <= a < b
    } else if (scenario == 2) {
        // Small impossible: small non-power-of-two denominator
        while (true) {
            b = rnd.next(3, 30);
            if (isPowerOfTwo(b)) continue;
            a = rnd.next(1, b - 1);
            if (std::gcd(a, b) == 1) break;
        }
    } else if (scenario == 3) {
        // Edge: 1/2 or (b-1)/b with small/medium power-of-two b
        if (rnd.next(0, 1) == 0) {
            a = 1;
            b = 2;
        } else {
            int q = rnd.next(2, 10); // b = 4..1024
            b = 1 << q;
            a = b - 1; // always odd, gcd(a,b)=1
        }
    } else if (scenario == 4) {
        // Large power-of-two denominator, various numerators
        int q = rnd.next(15, 29); // b up to 2^29 <= 1e9
        b = 1 << q;
        int pattern = rnd.next(1, 3);
        if (pattern == 1) {
            a = 1;
        } else if (pattern == 2) {
            a = b - 1;
        } else {
            int lo = b / 4;
            int hi = b / 2;
            if (lo % 2 == 0) lo++;
            if (hi % 2 == 0) hi--;
            if (lo > hi) {
                a = 1;
            } else {
                int count = (hi - lo) / 2 + 1;
                int idx = rnd.next(0, count - 1);
                a = lo + 2 * idx; // odd in [lo,hi]
            }
        }
    } else if (scenario == 5) {
        // Large impossible: big non-power-of-two denominator
        while (true) {
            b = rnd.next((int)1e8, (int)1e9);
            if (isPowerOfTwo(b)) continue;
            a = rnd.next(1, b - 1);
            if (std::gcd(a, b) == 1) break;
        }
    } else if (scenario == 6) {
        // Mixed random: sometimes representable, sometimes not
        bool wantPow = rnd.next(0, 1);
        if (wantPow) {
            // representable: random power-of-two denominator
            int q = rnd.next(1, 29);
            b = 1 << q;
            int maxK = (b / 2) - 1;
            int k = rnd.next(0, maxK);
            a = 2 * k + 1; // odd, 1 <= a < b
        } else {
            // impossible: random non-power-of-two
            while (true) {
                b = rnd.next(2, (int)1e9);
                if (isPowerOfTwo(b)) continue;
                a = rnd.next(1, b - 1);
                if (std::gcd(a, b) == 1) break;
            }
        }
    }

    // Occasionally force a small fixed interesting case (including samples)
    if (rnd.next(0, 9) == 0) { // 10% chance
        vector<pair<int,int>> fixedCases = {
            {1, 4},  // sample representable
            {5, 7},  // sample impossible
            {3, 8},
            {7, 8},
            {5, 16},
            {1, 2}
        };
        auto p = rnd.any(fixedCases);
        a = p.first;
        b = p.second;
    }

    println(a, b);
    return 0;
}
