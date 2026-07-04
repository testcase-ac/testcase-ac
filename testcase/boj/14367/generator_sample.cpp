#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int, int>> cases;

    auto addCase = [&](int jackets, int pants, int shirts, int limit) {
        cases.emplace_back(jackets, pants, shirts, limit);
    };

    addCase(1, 1, 1, rnd.any(vector<int>{1, 10}));
    addCase(1, 1, 3, rnd.next(1, 3));
    addCase(1, 2, 3, rnd.next(1, 3));
    addCase(3, 3, 3, rnd.any(vector<int>{1, 2, 3, 10}));

    int extraCases = rnd.next(8, 24);
    for (int i = 0; i < extraCases; ++i) {
        int jackets = rnd.next(1, 3);
        int pants = rnd.next(jackets, 3);
        int shirts = rnd.next(pants, 3);

        int limit;
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            limit = 1;
        } else if (mode == 1) {
            limit = rnd.next(1, shirts);
        } else if (mode == 2) {
            limit = shirts;
        } else {
            limit = rnd.next(4, 10);
        }

        addCase(jackets, pants, shirts, limit);
    }

    shuffle(cases.begin(), cases.end());
    println(static_cast<int>(cases.size()));
    for (auto [jackets, pants, shirts, limit] : cases) {
        println(jackets, pants, shirts, limit);
    }

    return 0;
}
