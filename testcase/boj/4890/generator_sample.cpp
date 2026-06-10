#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 5);
    int testCount = rnd.next(4, 14);

    auto addCase = [&](int w, int h) {
        w = max(1, min(w, 999999));
        h = max(1, min(h, 999999));
        cases.push_back({w, h});
    };

    for (int i = 0; i < testCount; ++i) {
        int localMode = (mode + i + rnd.next(0, 2)) % 6;
        if (localMode == 0) {
            addCase(rnd.next(1, 12), rnd.next(1, 12));
        } else if (localMode == 1) {
            int base = rnd.next(1, 80);
            addCase(base * rnd.next(1, 8), base * rnd.next(1, 8));
        } else if (localMode == 2) {
            int w = rnd.any(vector<int>{1, 2, 3, 5, 8, 13, 21, 34});
            int h = rnd.any(vector<int>{55, 89, 144, 233, 377, 610});
            addCase(w, h);
        } else if (localMode == 3) {
            int side = rnd.next(1, 999);
            addCase(side, side);
        } else if (localMode == 4) {
            addCase(rnd.next(999900, 999999), rnd.next(1, 99));
        } else {
            int w = rnd.next(900000, 999999);
            int h = rnd.next(900000, 999999);
            addCase(w, h);
        }
    }

    shuffle(cases.begin(), cases.end());
    for (const auto& tile : cases) {
        println(tile.first, tile.second);
    }
    println(0, 0);

    return 0;
}
