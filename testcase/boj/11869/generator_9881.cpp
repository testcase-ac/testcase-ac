#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> p;
    int scenario = rnd.next(0, 7);

    switch (scenario) {
        case 0: {
            // Single coin, small / medium / large position
            long long vals[] = {1, 2, 3, 4, 5, 10, 100, 1000, 1000000, 1000000000LL};
            p.push_back(rnd.any(vector<long long>(vals, vals + 10)));
            break;
        }

        case 1: {
            // Two equal coins (always losing position)
            int mode = rnd.next(0, 2);
            long long x;
            if (mode == 0) x = rnd.next(1, 20);
            else if (mode == 1) x = rnd.next(1000, 100000);
            else x = rnd.next(100000000, 1000000000);
            p.push_back(x);
            p.push_back(x);
            break;
        }

        case 2: {
            // Few coins, small coordinates, many duplicates possible
            int M = rnd.next(2, 6);
            for (int i = 0; i < M; i++) {
                if (i > 0 && rnd.next(0, 1) == 0) {
                    // duplicate some previous position
                    p.push_back(rnd.any(p));
                } else {
                    p.push_back(rnd.next(1, 15));
                }
            }
            break;
        }

        case 3: {
            // Mixed case, medium number of coins, mixture of small and large with duplicates
            int M = rnd.next(5, 30);
            int B = rnd.next(1, min(5, M));
            vector<long long> base;
            for (int i = 0; i < B; i++)
                base.push_back(rnd.next(1, 20));

            for (int i = 0; i < M; i++) {
                int r = rnd.next(0, 99);
                long long val;
                if (r < 50) {
                    // mostly from small base values
                    val = rnd.any(base);
                } else if (r < 75 && !p.empty()) {
                    // sometimes copy existing values
                    val = rnd.any(p);
                } else {
                    // some wider random values
                    int mode = rnd.next(0, 2);
                    if (mode == 0) val = rnd.next(1, 100);
                    else if (mode == 1) val = rnd.next(100000, 10000000);
                    else val = rnd.next(1, 1000000000);
                }
                p.push_back(val);
            }
            break;
        }

        case 4: {
            // Forced losing position: XOR of all positions is 0
            // Restrict positions so that XOR still fits safely within [1, 1e9]
            int M = rnd.next(2, 25);
            while (true) {
                p.clear();
                long long xorsum = 0;
                for (int i = 0; i < M - 1; i++) {
                    long long pos = rnd.next(1, 200000000); // < 2^28
                    p.push_back(pos);
                    xorsum ^= pos;
                }
                if (xorsum == 0) continue; // would make last = 0, not allowed
                long long last = xorsum;   // ensures total XOR = 0
                p.push_back(last);
                break;
            }
            break;
        }

        case 5: {
            // Forced winning position, many duplicates and some randomness
            int M = rnd.next(3, 30);
            int K = rnd.next(1, min(5, M));
            vector<long long> base;
            for (int i = 0; i < K; i++) {
                int mode = rnd.next(0, 2);
                long long val;
                if (mode == 0) val = rnd.next(1, 30);
                else if (mode == 1) val = rnd.next(100, 10000);
                else val = rnd.next(900000000, 1000000000);
                base.push_back(val);
            }

            for (int i = 0; i < M; i++) {
                long long val;
                int r = rnd.next(0, 99);
                if (r < 70) {
                    val = rnd.any(base);          // often from base values
                } else if (r < 85 && !p.empty()) {
                    val = rnd.any(p);             // sometimes repeat an existing position
                } else {
                    val = rnd.next(1, 1000000000); // fresh random
                }
                p.push_back(val);
            }

            // Ensure XOR != 0 (winning)
            while (true) {
                long long xorsum = 0;
                for (long long v : p) xorsum ^= v;
                if (xorsum != 0) break;
                int idx = rnd.next(0, (int)p.size() - 1);
                long long cur = p[idx];
                long long cand;
                do {
                    cand = rnd.next(1, 1000000000);
                } while (cand == cur);
                p[idx] = cand;
            }
            break;
        }

        case 6: {
            // Positions concentrated near large values and powers of two
            int M = rnd.next(1, 10);
            for (int i = 0; i < M; i++) {
                int mode = rnd.next(0, 2);
                long long val;
                if (mode == 0) {
                    val = 1000000000LL - rnd.next(0, 50); // near upper bound
                } else if (mode == 1) {
                    int k = rnd.next(20, 29);             // powers of two up to 2^29
                    val = 1LL << k;
                } else {
                    val = rnd.next(500000000, 1000000000);
                }
                // sometimes duplicate a previous large value
                if (i > 0 && rnd.next(0, 3) == 0) {
                    val = rnd.any(p);
                }
                p.push_back(val);
            }
            break;
        }

        case 7: {
            // Losing position with many even multiplicities (overall XOR = 0)
            int M = 2 * rnd.next(1, 15); // even, between 2 and 30
            int cur = 0;
            while (cur < M) {
                long long val = rnd.next(1, 50);
                int remaining = M - cur;
                int maxPairs = remaining / 2;
                int pairs = rnd.next(1, maxPairs); // at least one pair
                for (int j = 0; j < pairs * 2; j++)
                    p.push_back(val);
                cur += pairs * 2;
            }
            // XOR is 0 because each value appears an even number of times
            break;
        }
    }

    int M = (int)p.size();
    println(M);
    for (int i = 0; i < M; i++) {
        if (i) printf(" ");
        printf("%lld", p[i]);
    }
    printf("\n");

    return 0;
}
