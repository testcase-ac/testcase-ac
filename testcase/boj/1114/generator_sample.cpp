#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long L;
    int K;
    int C;
    vector<long long> positions;

    if (mode == 0) {
        L = rnd.next(2LL, 12LL);
        K = rnd.next(1, 12);
        C = rnd.next(1, 12);
        for (int i = 0; i < K; ++i) {
            positions.push_back(rnd.next(1LL, L));
        }
    } else if (mode == 1) {
        L = rnd.next(2LL, 30LL);
        K = rnd.next(6, 18);
        C = rnd.next(1, min(10, K + 3));
        vector<long long> pool;
        pool.push_back(1);
        pool.push_back(L);
        pool.push_back((L + 1) / 2);
        for (int i = 0; i < 3; ++i) {
            pool.push_back(rnd.next(1LL, L));
        }
        for (int i = 0; i < K; ++i) {
            positions.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        L = rnd.next(20LL, 120LL);
        K = rnd.next(5, 20);
        C = rnd.next(1, min(8, K));
        long long center = rnd.next(2LL, L - 1);
        long long radius = rnd.next(1LL, min(10LL, L - 1));
        for (int i = 0; i < K; ++i) {
            long long lo = max(1LL, center - radius);
            long long hi = min(L, center + radius);
            positions.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        L = rnd.next(40LL, 250LL);
        K = rnd.next(8, 28);
        C = rnd.next(1, min(12, K));
        for (int i = 0; i < K; ++i) {
            long long value;
            if (rnd.next(0, 4) == 0) {
                value = rnd.any(vector<long long>{1, 2, L - 1, L});
            } else {
                value = rnd.next(1LL, L);
            }
            positions.push_back(value);
        }
    } else if (mode == 4) {
        L = rnd.next(100000000LL, 1000000000LL);
        K = rnd.next(3, 15);
        C = rnd.next(1, 10000);
        for (int i = 0; i < K; ++i) {
            if (rnd.next(0, 3) == 0) {
                positions.push_back(rnd.any(vector<long long>{1LL, L, L / 2, L - 1}));
            } else {
                positions.push_back(rnd.next(1LL, L));
            }
        }
    } else {
        L = rnd.next(2LL, 80LL);
        K = rnd.next(1, 25);
        C = rnd.next(K, 10000);
        long long step = max(1LL, L / rnd.next(2LL, 8LL));
        for (int i = 0; i < K; ++i) {
            long long base = min(L, 1 + step * rnd.next(0, 7));
            long long jitter = rnd.next(0LL, min(3LL, L - 1));
            positions.push_back(min(L, max(1LL, base + jitter)));
        }
    }

    shuffle(positions.begin(), positions.end());

    println(L, K, C);
    println(positions);

    return 0;
}
