#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 2147483647LL;
    vector<long long> bets;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        // Empty bet sequence accepted by the local validator.
    } else if (mode == 1) {
        bets.push_back(rnd.next(1LL, LIMIT));
    } else if (mode == 2) {
        long long remaining = LIMIT - rnd.next(0, 30);
        int n = rnd.next(2, 8);
        for (int i = 0; i < n - 1; ++i) {
            long long maxTake = remaining - (n - 1 - i);
            long long take = rnd.next(1LL, maxTake / (n - i) + 1);
            bets.push_back(take);
            remaining -= take;
        }
        bets.push_back(remaining);
        shuffle(bets.begin(), bets.end());
    } else if (mode == 3) {
        int n = rnd.next(2, 25);
        long long start = rnd.next(1, 20);
        long long step = rnd.next(0, 15);
        for (int i = 0; i < n; ++i) {
            bets.push_back(start + step * i + rnd.next(0, 3));
        }
    } else if (mode == 4) {
        int n = rnd.next(5, 45);
        long long cap = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            bets.push_back(rnd.next(1LL, cap));
        }
    } else {
        int n = rnd.next(1, 40);
        long long remaining = rnd.next(1LL, LIMIT);
        for (int i = 0; i < n; ++i) {
            long long minLeft = n - 1 - i;
            long long take = rnd.next(1LL, remaining - minLeft);
            bets.push_back(take);
            remaining -= take;
        }
        shuffle(bets.begin(), bets.end());
    }

    for (long long bet : bets) {
        println(bet);
    }
    println(-1);

    return 0;
}
