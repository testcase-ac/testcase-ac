#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

const int MIN_PILE = 1;
const int MAX_PILE = 200;

array<int, 3> shuffledTriple(int x, int y, int z) {
    array<int, 3> piles = {x, y, z};
    shuffle(piles.begin(), piles.end());
    return piles;
}

array<int, 3> randomTriple() {
    return shuffledTriple(rnd.next(MIN_PILE, MAX_PILE),
                          rnd.next(MIN_PILE, MAX_PILE),
                          rnd.next(MIN_PILE, MAX_PILE));
}

array<int, 3> xorZeroTriple() {
    for (;;) {
        int x = rnd.next(MIN_PILE, MAX_PILE);
        int y = rnd.next(MIN_PILE, MAX_PILE);
        int z = x ^ y;
        if (MIN_PILE <= z && z <= MAX_PILE) return shuffledTriple(x, y, z);
    }
}

array<int, 3> nearXorZeroTriple() {
    array<int, 3> piles = xorZeroTriple();
    int idx = rnd.next(0, 2);
    int delta = rnd.any(vector<int>{-7, -3, -1, 1, 3, 7});
    piles[idx] = max(MIN_PILE, min(MAX_PILE, piles[idx] + delta));
    return piles;
}

array<int, 3> equalOrPairedTriple() {
    int a = rnd.next(MIN_PILE, MAX_PILE);
    if (rnd.next(0, 1) == 0) return shuffledTriple(a, a, a);

    int b = rnd.next(MIN_PILE, MAX_PILE);
    return shuffledTriple(a, a, b);
}

array<int, 3> boundaryTriple() {
    vector<int> values = {1, 2, 3, 4, 7, 8, 15, 16, 31, 32,
                          63, 64, 127, 128, 199, 200};
    return shuffledTriple(rnd.any(values), rnd.any(values), rnd.any(values));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(12, 45);
    vector<array<int, 3>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 99);
        if (mode < 25) {
            cases.push_back(xorZeroTriple());
        } else if (mode < 45) {
            cases.push_back(nearXorZeroTriple());
        } else if (mode < 65) {
            cases.push_back(equalOrPairedTriple());
        } else if (mode < 85) {
            cases.push_back(boundaryTriple());
        } else {
            cases.push_back(randomTriple());
        }
    }

    println(t);
    for (const auto& piles : cases) println(piles[0], piles[1], piles[2]);

    return 0;
}
