#include "testlib.h"
#include <array>

using namespace std;

array<int, 3> randomLineup(int lo, int hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi), rnd.next(lo, hi)};
}

array<int, 3> lineupWithScore(int target) {
    int minThrees = max(0, (target - 200 + 2) / 3);
    int maxThrees = min(100, target / 3);
    int threes = rnd.next(minThrees, maxThrees);
    int remainder = target - 3 * threes;
    int minTwos = max(0, (remainder - 100 + 1) / 2);
    int maxTwos = min(100, remainder / 2);
    int twos = rnd.next(minTwos, maxTwos);
    int ones = remainder - 2 * twos;
    return {threes, twos, ones};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 3> apples;
    array<int, 3> bananas;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        apples = randomLineup(0, 100);
        bananas = randomLineup(0, 100);
    } else if (mode == 1) {
        apples = randomLineup(0, 8);
        bananas = randomLineup(0, 8);
    } else if (mode == 2) {
        int edge = rnd.next(0, 1) ? 100 : 0;
        apples = {edge, edge, edge};
        bananas = randomLineup(0, 100);
    } else if (mode == 3) {
        int target = rnd.next(0, 300);
        apples = lineupWithScore(target);
        bananas = lineupWithScore(target);
    } else if (mode == 4) {
        int target = rnd.next(1, 299);
        apples = lineupWithScore(target + 1);
        bananas = lineupWithScore(target);
    } else {
        int target = rnd.next(0, 299);
        apples = lineupWithScore(target);
        bananas = lineupWithScore(target + 1);
    }

    for (int x : apples) println(x);
    for (int x : bananas) println(x);

    return 0;
}
