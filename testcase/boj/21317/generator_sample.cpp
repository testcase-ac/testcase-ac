#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int boundedCost(int value) {
    return max(1, min(5000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(18, 20);
    } else {
        n = rnd.next(4, 14);
    }

    vector<pair<int, int>> jumps;
    jumps.reserve(max(0, n - 1));

    int base = rnd.next(1, 40);
    for (int i = 1; i <= n - 1; ++i) {
        int smallJump;
        int bigJump;

        if (mode == 0) {
            smallJump = rnd.next(1, 5000);
            bigJump = rnd.next(1, 5000);
        } else if (mode == 1) {
            smallJump = rnd.next(4800, 5000);
            bigJump = rnd.next(4800, 5000);
        } else if (mode == 2) {
            smallJump = (i % 2 == 0) ? rnd.next(1, 8) : rnd.next(200, 700);
            bigJump = (i % 2 == 0) ? rnd.next(200, 700) : rnd.next(1, 8);
        } else if (mode == 3) {
            smallJump = boundedCost(base + rnd.next(-3, 3));
            bigJump = boundedCost(2 * base + rnd.next(-5, 15));
        } else if (mode == 4) {
            smallJump = rnd.next(1, 25);
            bigJump = rnd.next(1000, 5000);
        } else {
            smallJump = rnd.next(1000, 5000);
            bigJump = rnd.next(1, 25);
        }

        jumps.push_back({smallJump, bigJump});
    }

    int k;
    if (mode <= 1) {
        k = rnd.next(1, 5000);
    } else if (mode == 2 || mode == 4) {
        k = rnd.next(1, 20);
    } else if (mode == 5) {
        k = rnd.next(3000, 5000);
    } else {
        k = boundedCost(base + rnd.next(-5, 20));
    }

    println(n);
    for (auto [smallJump, bigJump] : jumps) {
        println(smallJump, bigJump);
    }
    println(k);

    return 0;
}
