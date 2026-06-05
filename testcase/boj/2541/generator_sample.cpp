#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int MAX_COORD = 100000;

int clampCoord(int x) {
    return max(1, min(MAX_COORD, x));
}

pair<int, int> makeReachable(int a, int b, int oddDiff) {
    if (a == b) {
        int v = rnd.next(1, MAX_COORD);
        return {v, v};
    }

    int maxMult = max(1, (MAX_COORD - 1) / oddDiff);
    int mult = rnd.next(1, min(12, maxMult));
    int delta = oddDiff * mult;
    if (a < b) {
        int p = rnd.next(1, MAX_COORD - delta);
        return {p, p + delta};
    }

    int q = rnd.next(1, MAX_COORD - delta);
    return {q + delta, q};
}

pair<int, int> makeUnreachable(int a, int b, int oddDiff) {
    if (a == b) {
        int p = rnd.next(1, MAX_COORD - 1);
        int q = rnd.next(p + 1, MAX_COORD);
        if (rnd.next(2)) swap(p, q);
        return {p, q};
    }

    for (int tries = 0; tries < 100; ++tries) {
        int p = rnd.next(1, MAX_COORD);
        int q = rnd.next(1, MAX_COORD);
        int delta = abs(p - q);
        bool sameDirection = (a < b && p < q) || (a > b && p > q);
        if (!sameDirection || delta % oddDiff != 0) return {p, q};
    }

    if (a < b) return {2, 1};
    return {1, 2};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a, b;
    if (mode == 0) {
        a = b = rnd.next(1, MAX_COORD);
    } else if (mode == 1) {
        a = rnd.next(1, 20);
        b = rnd.next(a + 1, min(MAX_COORD, a + 30));
    } else if (mode == 2) {
        b = rnd.next(1, 20);
        a = rnd.next(b + 1, min(MAX_COORD, b + 30));
    } else if (mode == 3) {
        int base = rnd.next(1, 50000);
        int odd = rnd.next(1, 99) * 2 - 1;
        int power = 1 << rnd.next(0, 8);
        int diff = min(MAX_COORD - base, odd * power);
        a = base;
        b = base + diff;
    } else {
        vector<pair<int, int>> anchors = {
            {1, MAX_COORD},
            {MAX_COORD, 1},
            {1, 1},
            {MAX_COORD, MAX_COORD},
            {50000, 50001},
        };
        tie(a, b) = rnd.any(anchors);
    }

    int oddDiff = abs(a - b);
    while (oddDiff > 0 && oddDiff % 2 == 0) oddDiff /= 2;
    if (oddDiff == 0) oddDiff = 1;

    vector<pair<int, int>> queries;
    queries.push_back(makeReachable(a, b, oddDiff));
    queries.push_back(makeUnreachable(a, b, oddDiff));
    queries.push_back({clampCoord(a + rnd.next(0, 3)), clampCoord(b + rnd.next(0, 3))});
    queries.push_back(rnd.any(vector<pair<int, int>>{
        {1, 1},
        {1, MAX_COORD},
        {MAX_COORD, 1},
        {MAX_COORD, MAX_COORD},
    }));
    queries.push_back(rnd.next(2) ? makeReachable(a, b, oddDiff) : makeUnreachable(a, b, oddDiff));

    shuffle(queries.begin(), queries.end());

    println(a, b);
    for (auto [p, q] : queries) println(p, q);

    return 0;
}
