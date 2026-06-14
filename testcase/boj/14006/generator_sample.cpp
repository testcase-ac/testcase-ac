#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 0;
    } else if (mode == 7) {
        n = rnd.next(16, 18);
    } else {
        n = rnd.next(1, 6);
    }

    int players = 1 << n;
    long long dudu;
    vector<long long> scores(players);

    if (mode == 0) {
        dudu = rnd.next(0LL, 1000000000LL);
        scores[0] = dudu;
    } else if (mode == 1) {
        dudu = rnd.next(0LL, 1000000000LL);
        for (int i = 0; i < players; ++i) scores[i] = dudu;
    } else if (mode == 2) {
        dudu = rnd.next(1LL, 1000000000LL);
        scores[0] = dudu;
        int weak = rnd.next(1, players - 1);
        for (int i = 1; i < players; ++i) {
            scores[i] = rnd.next(dudu, 1000000000LL);
        }
        scores[weak] = rnd.next(0LL, dudu - 1);
    } else if (mode == 3) {
        dudu = rnd.next(0LL, 999999999LL);
        scores[0] = dudu;
        for (int i = 1; i < players; ++i) {
            scores[i] = rnd.next(dudu + 1, 1000000000LL);
        }
    } else if (mode == 4) {
        dudu = rnd.next(0LL, 3LL);
        scores[0] = dudu;
        for (int i = 1; i < players; ++i) {
            scores[i] = rnd.any(vector<long long>{0LL, dudu, dudu + 1, 1000000000LL});
            if (scores[i] > 1000000000LL) scores[i] = 1000000000LL;
        }
    } else if (mode == 5) {
        dudu = rnd.next(999999996LL, 1000000000LL);
        scores[0] = dudu;
        for (int i = 1; i < players; ++i) {
            scores[i] = rnd.next(999999990LL, 1000000000LL);
        }
    } else {
        dudu = rnd.next(0LL, 1000000000LL);
        scores[0] = dudu;
        long long lo = rnd.next(0LL, dudu);
        long long hi = rnd.next(dudu, 1000000000LL);
        for (int i = 1; i < players; ++i) {
            scores[i] = rnd.next(lo, hi);
        }
    }

    println(n);
    for (long long score : scores) {
        println(score);
    }

    return 0;
}
