#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> randomCase() {
    int mode = rnd.next(0, 7);
    if (mode == 0) return {1, rnd.next(1, 1000000)};
    if (mode == 1) return {rnd.next(1, 1000000), 1};
    if (mode == 2) {
        int side = rnd.next(1, 1000000);
        return {side, side};
    }
    if (mode == 3) return {rnd.next(2, 30), rnd.next(2, 30)};
    if (mode == 4) return {rnd.next(999900, 1000000), rnd.next(999900, 1000000)};
    if (mode == 5) return {rnd.next(2, 50), rnd.next(999900, 1000000)};
    if (mode == 6) return {rnd.next(999900, 1000000), rnd.next(2, 50)};
    return {rnd.next(1, 1000000), rnd.next(1, 1000000)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {1, 1},
        {2, 2},
        {2, 3},
        {3, 2},
        {10, 10},
        {1, 1000000},
        {1000000, 1},
        {1000000, 1000000},
    };

    int extra = rnd.next(4, 18);
    for (int i = 0; i < extra; ++i) {
        cases.push_back(randomCase());
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (auto [r, c] : cases) {
        println(r, c);
    }

    return 0;
}
