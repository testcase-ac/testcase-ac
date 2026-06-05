#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int oddWithLevels(int levels) {
    int block = 1;
    for (int i = 0; i < levels; ++i) block *= 2;
    int maxTail = (1000000000 - (block - 1)) / block;
    int tail = rnd.next(0, maxTail);
    return tail * block + block - 1;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        cases.push_back({rnd.next(1, 30), rnd.next(1, 30)});
    } else if (mode == 1) {
        int n = rnd.next(1, 15) * 2;
        int m = rnd.next(1, 15) * 2 - 1;
        cases.push_back({n, m});
    } else if (mode == 2) {
        int levels = rnd.next(1, 8);
        cases.push_back({oddWithLevels(levels), oddWithLevels(levels)});
    } else if (mode == 3) {
        int nLevels = rnd.next(1, 10);
        int mLevels = rnd.next(1, 10);
        cases.push_back({oddWithLevels(nLevels), oddWithLevels(mLevels)});
    } else if (mode == 4) {
        int base = rnd.next(1, 500000000);
        cases.push_back({base * 2, rnd.next(1, 500000000) * 2 - 1});
    } else if (mode == 5) {
        cases.push_back({1, rnd.next(1, 1000000000)});
    } else {
        int n = rnd.next(999999900, 1000000000);
        int m = rnd.next(999999900, 1000000000);
        cases.push_back({n, m});
    }

    auto selected = rnd.any(cases);
    if (rnd.next(0, 1)) swap(selected.first, selected.second);
    println(selected.first, selected.second);

    return 0;
}
