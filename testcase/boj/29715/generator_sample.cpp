#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(3, 9);
        m = 0;
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(3, 9);
        m = rnd.next(1, n);
    } else if (mode == 3) {
        n = rnd.next(3, 9);
        m = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{3, 9});
        m = rnd.next(max(0, n - 2), n);
    } else {
        n = rnd.next(3, 9);
        m = rnd.next(0, n);
    }

    int x = (mode == 4 ? rnd.any(vector<int>{1, 10}) : rnd.next(1, 10));
    int y = (mode <= 1 ? rnd.any(vector<int>{1, 10}) : rnd.next(1, 10));

    vector<int> positions(n);
    iota(positions.begin(), positions.end(), 1);
    shuffle(positions.begin(), positions.end());

    vector<int> digits(9);
    iota(digits.begin(), digits.end(), 1);
    shuffle(digits.begin(), digits.end());

    int fixedCount;
    if (m == 0) {
        fixedCount = 0;
    } else if (mode == 1) {
        fixedCount = m;
    } else if (mode == 2) {
        fixedCount = 0;
    } else if (mode == 3) {
        fixedCount = rnd.next(1, m);
    } else if (mode == 4) {
        fixedCount = rnd.next(0, m);
    } else {
        fixedCount = rnd.next(0, m);
    }

    vector<pair<int, int>> info;
    for (int i = 0; i < fixedCount; ++i) {
        info.emplace_back(positions[i], digits[i]);
    }
    for (int i = fixedCount; i < m; ++i) {
        info.emplace_back(0, digits[i]);
    }
    shuffle(info.begin(), info.end());

    println(n, m);
    println(x, y);
    for (auto [a, b] : info) {
        println(a, b);
    }

    return 0;
}
