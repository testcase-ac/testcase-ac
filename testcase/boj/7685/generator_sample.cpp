#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_K = 1000000000;

vector<int> makeLosingCase(int n, int maxValue) {
    vector<int> piles;
    int xorsum = 0;
    for (int i = 0; i + 1 < n; ++i) {
        int value = rnd.next(1, maxValue);
        piles.push_back(value);
        xorsum ^= value;
    }
    if (xorsum == 0 || xorsum > MAX_K) {
        piles.push_back(rnd.next(1, maxValue));
    } else {
        piles.push_back(xorsum);
    }
    shuffle(piles.begin(), piles.end());
    return piles;
}

vector<int> makeBoundaryCase() {
    vector<int> candidates = {
        1,
        2,
        3,
        7,
        15,
        31,
        1023,
        65535,
        536870912,
        999999937,
        1000000000,
    };
    int n = rnd.next(2, 8);
    vector<int> piles;
    for (int i = 0; i < n; ++i) {
        piles.push_back(rnd.any(candidates));
    }
    return piles;
}

vector<int> makePowerCase() {
    int n = rnd.next(2, 12);
    vector<int> piles;
    for (int i = 0; i < n; ++i) {
        int bit = rnd.next(0, 29);
        int value = 1 << bit;
        if (rnd.next(0, 3) == 0 && value < MAX_K) {
            value = min(MAX_K, value + rnd.next(1, min(value, 1000)));
        }
        piles.push_back(value);
    }
    return piles;
}

vector<int> makeRandomCase() {
    int n = rnd.next(2, 30);
    int maxValue = rnd.any(vector<int>{10, 100, 1000, 1000000, MAX_K});
    vector<int> piles;
    for (int i = 0; i < n; ++i) {
        piles.push_back(rnd.next(1, maxValue));
    }
    return piles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(6, 12);
    for (int tc = 0; tc < caseCount; ++tc) {
        vector<int> piles;
        int mode = tc < 5 ? tc : rnd.next(0, 4);

        if (mode == 0) {
            piles = {rnd.next(1, MAX_K)};
        } else if (mode == 1) {
            int n = rnd.next(2, 16);
            piles = makeLosingCase(n, rnd.any(vector<int>{15, 255, 65535, 1000000}));
        } else if (mode == 2) {
            piles = makeBoundaryCase();
        } else if (mode == 3) {
            piles = makePowerCase();
        } else {
            piles = makeRandomCase();
        }

        println((int)piles.size());
        println(piles);
    }

    println(0);
    return 0;
}
