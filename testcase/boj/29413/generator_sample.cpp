#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_K = 1000000000000000000LL;
    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        7LL,
        8LL,
        9LL,
        10LL,
        26LL,
        27LL,
        28LL,
        99LL,
        100LL,
        101LL,
        999LL,
        1000LL,
        1001LL,
        MAX_K - 2,
        MAX_K - 1,
        MAX_K,
    };

    long long k;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        k = rnd.next(1LL, 30LL);
    } else if (mode == 1) {
        k = rnd.any(anchors);
    } else if (mode == 2) {
        long long base = 1;
        int exponent = rnd.next(0, 18);
        for (int i = 0; i < exponent; ++i) {
            base *= 10;
        }
        long long offset = rnd.next(-20LL, 20LL);
        k = min(MAX_K, max(1LL, base + offset));
    } else if (mode == 3) {
        k = rnd.next(1LL, 1000000LL);
    } else if (mode == 4) {
        k = rnd.next(1000000LL, 1000000000000LL);
    } else {
        k = rnd.next(1LL, MAX_K);
    }

    println(k);
    return 0;
}
