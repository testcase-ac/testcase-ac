#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(0, 3);
    int playerCount = 1 << n;
    int mode = rnd.next(0, 5);

    long long dudu = 0;
    vector<long long> scores(playerCount);

    if (n == 0) {
        scores[0] = rnd.any(vector<long long>{0LL, 1LL, 1000000000LL, rnd.next(0LL, 1000000000LL)});
    } else if (mode == 0) {
        dudu = rnd.next(0LL, 20LL);
        scores[0] = dudu;
        for (int i = 1; i < playerCount; ++i) {
            scores[i] = rnd.next(dudu + 1, min(1000000000LL, dudu + 30));
        }
    } else if (mode == 1) {
        dudu = rnd.next(0LL, 100LL);
        scores[0] = dudu;
        int witness = rnd.next(1, playerCount - 1);
        for (int i = 1; i < playerCount; ++i) {
            scores[i] = rnd.next(dudu + 1, min(1000000000LL, dudu + 100));
        }
        scores[witness] = rnd.next(0LL, dudu);
    } else if (mode == 2) {
        dudu = rnd.next(0LL, 1000000000LL);
        scores[0] = dudu;
        int witness = rnd.next(1, playerCount - 1);
        for (int i = 1; i < playerCount; ++i) {
            scores[i] = rnd.next(0LL, 1000000000LL);
        }
        scores[witness] = dudu;
    } else if (mode == 3) {
        dudu = rnd.any(vector<long long>{0LL, 1LL, 999999999LL, 1000000000LL});
        scores[0] = dudu;
        for (int i = 1; i < playerCount; ++i) {
            scores[i] = rnd.any(vector<long long>{0LL, 1LL, 2LL, 999999998LL, 999999999LL, 1000000000LL});
        }
    } else {
        long long lo = rnd.next(0LL, 50LL);
        long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 200LL)));
        dudu = rnd.next(lo, hi);
        scores[0] = dudu;
        for (int i = 1; i < playerCount; ++i) {
            scores[i] = rnd.next(lo, hi);
        }
    }

    println(n);
    for (long long score : scores) {
        println(score);
    }

    return 0;
}
